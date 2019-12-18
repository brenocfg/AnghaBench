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

/* Variables and functions */
 size_t strlcpy (char*,char const*,size_t) ; 
 size_t strlen (char const*) ; 
 size_t strnlen (char*,size_t) ; 

size_t
strlcat(char *dst, const char *src, size_t siz)
{
#if 1
	char *d = dst;
	const char *s = src;
	size_t n = siz;
	size_t dlen;

	/* Find the end of dst and adjust bytes left but don't go past end */
	while (n-- != 0 && *d != '\0')
		d++;
	dlen = d - dst;
	n = siz - dlen;

	if (n == 0)
		return(dlen + strlen(s));
	while (*s != '\0') {
		if (n != 1) {
			*d++ = *s;
			n--;
		}
		s++;
	}
	*d = '\0';

	return(dlen + (s - src));	/* count does not include NUL */
#else

	/*
	 * Find length of string in dst (maxing out at siz).
	 */
	size_t dlen = strnlen(dst, siz);

	/*
	 * Copy src into any remaining space in dst (truncating if needed).
	 * Note strlcpy(dst, src, 0) returns strlen(src).
	 */
	return dlen + strlcpy(dst + dlen, src, siz - dlen);
#endif
}