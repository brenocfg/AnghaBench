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

int Util_sscandec(const char *s)
{
	int result;
	if (*s == '\0')
		return -1;
	result = 0;
	for (;;) {
		if (*s >= '0' && *s <= '9')
			result = 10 * result + *s - '0';
		else if (*s == '\0')
			return result;
		else
			return -1;
		s++;
	}
}