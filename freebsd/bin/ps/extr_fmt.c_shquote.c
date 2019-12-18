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
 int LONG_MAX ; 
 int SIZE_MAX ; 
 int VIS_CSTYLE ; 
 int VIS_NL ; 
 int /*<<< orphan*/  _SC_ARG_MAX ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 char* malloc (size_t) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  strvisx (char*,char*,size_t,int) ; 
 long sysconf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
shquote(char **argv)
{
	long arg_max;
	static size_t buf_size;
	size_t len;
	char **p, *dst, *src;
	static char *buf = NULL;

	if (buf == NULL) {
		if ((arg_max = sysconf(_SC_ARG_MAX)) == -1)
			errx(1, "sysconf _SC_ARG_MAX failed");
		if (arg_max >= LONG_MAX / 4 || arg_max >= (long)(SIZE_MAX / 4))
			errx(1, "sysconf _SC_ARG_MAX preposterously large");
		buf_size = 4 * arg_max + 1;
		if ((buf = malloc(buf_size)) == NULL)
			errx(1, "malloc failed");
	}

	if (*argv == NULL) {
		buf[0] = '\0';
		return (buf);
	}
	dst = buf;
	for (p = argv; (src = *p++) != NULL; ) {
		if (*src == '\0')
			continue;
		len = (buf_size - 1 - (dst - buf)) / 4;
		strvisx(dst, src, strlen(src) < len ? strlen(src) : len,
		    VIS_NL | VIS_CSTYLE);
		while (*dst != '\0')
			dst++;
		if ((buf_size - 1 - (dst - buf)) / 4 > 0)
			*dst++ = ' ';
	}
	/* Chop off trailing space */
	if (dst != buf && dst[-1] == ' ')
		dst--;
	*dst = '\0';
	return (buf);
}