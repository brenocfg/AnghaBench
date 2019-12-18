#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nlattr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,size_t) ; 
 char* nla_data (struct nlattr const*) ; 
 size_t nla_len (struct nlattr const*) ; 

size_t nla_strlcpy(char *dst, const struct nlattr *nla, size_t dstsize)
{
	size_t srclen = nla_len(nla);
	char *src = nla_data(nla);

	if (srclen > 0 && src[srclen - 1] == '\0')
		srclen--;

	if (dstsize > 0) {
		size_t len = (srclen >= dstsize) ? dstsize - 1 : srclen;

		memset(dst, 0, dstsize);
		memcpy(dst, src, len);
	}

	return srclen;
}