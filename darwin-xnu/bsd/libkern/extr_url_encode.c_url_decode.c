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
 char hex2int (int /*<<< orphan*/ ) ; 
 scalar_t__ isprint (char) ; 
 char* memmove (char*,char*,scalar_t__) ; 
 scalar_t__ strlen (char*) ; 

void
url_decode(char *str)
{
	if (!str) {
		return;
	}

	while (*str) {
		if (*str == '%') {
			char c = 0;
			char *esc = str++; /* remember the start of the escape sequence */

			if (*str) {
				c += hex2int(*str++);
			}
			if (*str) {
				c = (c << 4) + hex2int(*str++);
			}

			if (isprint(c)) {
				/* overwrite the '%' with the new char, and bump the rest of the
				 * string down a few characters */
				*esc++ = c;
				str = memmove(esc, str, strlen(str)+1);
			}
		} else {
			str++;
		}
	}
}