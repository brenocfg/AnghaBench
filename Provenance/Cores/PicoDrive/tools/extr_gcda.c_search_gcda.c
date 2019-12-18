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

__attribute__((used)) static int search_gcda(const char *str, int len)
{
	int i;
	for (i = 0; i < len - 6; i++)
		if (str[i]   == '.' && str[i+1] == 'g' && str[i+2] == 'c' &&
		    str[i+3] == 'd' && str[i+4] == 'a' && str[i+5] == 0)
			return i;
	return -1;
}