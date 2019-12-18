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
 char* malloc (size_t) ; 

char *
strchr2esc(const char *s, size_t n)
{
	const char *p;
	char *q, *s2, c;
	size_t addl = 0;

	for (p = s; p < s + n; p++) {
		switch (c = *p) {
		case '\0':
		case '\a':
		case '\b':
		case '\f':
		case '\n':
		case '\r':
		case '\t':
		case '\v':
		case '"':
		case '\\':
			addl++;		/* 1 add'l char needed to follow \ */
			break;
		case ' ':
			break;
		default:
			if (c < '!' || c > '~')
				addl += 3; /* 3 add'l chars following \ */
		}
	}

	if ((s2 = malloc(n + addl + 1)) == NULL)
		return (NULL);

	for (p = s, q = s2; p < s + n; p++) {
		switch (c = *p) {
		case '\0':
			*q++ = '\\';
			*q++ = '0';
			break;
		case '\a':
			*q++ = '\\';
			*q++ = 'a';
			break;
		case '\b':
			*q++ = '\\';
			*q++ = 'b';
			break;
		case '\f':
			*q++ = '\\';
			*q++ = 'f';
			break;
		case '\n':
			*q++ = '\\';
			*q++ = 'n';
			break;
		case '\r':
			*q++ = '\\';
			*q++ = 'r';
			break;
		case '\t':
			*q++ = '\\';
			*q++ = 't';
			break;
		case '\v':
			*q++ = '\\';
			*q++ = 'v';
			break;
		case '"':
			*q++ = '\\';
			*q++ = '"';
			break;
		case '\\':
			*q++ = '\\';
			*q++ = '\\';
			break;
		case ' ':
			*q++ = c;
			break;
		default:
			if (c < '!' || c > '~') {
				*q++ = '\\';
				*q++ = ((c >> 6) & 3) + '0';
				*q++ = ((c >> 3) & 7) + '0';
				*q++ = (c & 7) + '0';
			} else
				*q++ = c;
		}

		if (c == '\0')
			break; /* don't continue past \0 even if p < s + n */
	}

	*q = '\0';
	return (s2);
}