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
 scalar_t__ islower (char const) ; 

__attribute__((used)) static void
dt_header_fmt_macro(char *buf, const char *str)
{
	for (;;) {
		if (islower(*str)) {
			*buf++ = *str++ + 'A' - 'a';
		} else if (*str == '-') {
			*buf++ = '_';
			str++;
		} else if (*str == '.') {
			*buf++ = '_';
			str++;
		} else if ((*buf++ = *str++) == '\0') {
			break;
		}
	}
}