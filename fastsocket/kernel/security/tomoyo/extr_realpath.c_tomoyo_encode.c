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
 int ENOMEM ; 
 scalar_t__ tomoyo_is_valid (unsigned char const) ; 

int tomoyo_encode(char *buffer, int buflen, const char *str)
{
	while (1) {
		const unsigned char c = *(unsigned char *) str++;

		if (tomoyo_is_valid(c)) {
			if (--buflen <= 0)
				break;
			*buffer++ = (char) c;
			if (c != '\\')
				continue;
			if (--buflen <= 0)
				break;
			*buffer++ = (char) c;
			continue;
		}
		if (!c) {
			if (--buflen <= 0)
				break;
			*buffer = '\0';
			return 0;
		}
		buflen -= 4;
		if (buflen <= 0)
			break;
		*buffer++ = '\\';
		*buffer++ = (c >> 6) + '0';
		*buffer++ = ((c >> 3) & 7) + '0';
		*buffer++ = (c & 7) + '0';
	}
	return -ENOMEM;
}