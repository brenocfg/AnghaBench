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

void qword_add(char **bpp, int *lp, char *str)
{
	char *bp = *bpp;
	int len = *lp;
	char c;

	if (len < 0) return;

	while ((c=*str++) && len)
		switch(c) {
		case ' ':
		case '\t':
		case '\n':
		case '\\':
			if (len >= 4) {
				*bp++ = '\\';
				*bp++ = '0' + ((c & 0300)>>6);
				*bp++ = '0' + ((c & 0070)>>3);
				*bp++ = '0' + ((c & 0007)>>0);
			}
			len -= 4;
			break;
		default:
			*bp++ = c;
			len--;
		}
	if (c || len <1) len = -1;
	else {
		*bp++ = ' ';
		len--;
	}
	*bpp = bp;
	*lp = len;
}