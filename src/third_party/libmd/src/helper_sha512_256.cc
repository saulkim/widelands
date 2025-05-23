/*	$OpenBSD: helper.c,v 1.9 2010/01/08 13:30:21 oga Exp $	*/

/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <phk@login.dkuug.dk> wrote this file.  As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.   Poul-Henning Kamp
 * ----------------------------------------------------------------------------
 */

#include <sys/stat.h>

#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "third_party/libmd/include/sha2.h"

namespace libmd {

#ifndef MIN
# define MIN(x, y) (((x) < (y)) ? (x) : (y))
#endif

/* ARGSUSED */
char *
SHA512_256End(SHA2_CTX *ctx, char *buf)
{
	int i;
	uint8_t digest[SHA512_256_DIGEST_LENGTH];
	static const char hex[] = "0123456789abcdef";

	if (buf == NULL && (buf = (char*)malloc(SHA512_256_DIGEST_STRING_LENGTH)) == NULL)
		return (NULL);

	SHA512_256Final(digest, ctx);
	for (i = 0; i < SHA512_256_DIGEST_LENGTH; i++) {
		buf[i + i] = hex[digest[i] >> 4];
		buf[i + i + 1] = hex[digest[i] & 0x0f];
	}
	buf[i + i] = '\0';
	memset(digest, 0, sizeof(digest));
	return (buf);
}

char *
SHA512_256Data(const uint8_t *data, size_t len, char *buf)
{
	SHA2_CTX ctx;

	SHA512_256Init(&ctx);
	SHA512_256Update(&ctx, data, len);
	return (SHA512_256End(&ctx, buf));
}

}  // namespace libmd
