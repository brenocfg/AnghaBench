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
 int get_option (char**,int*) ; 
 int get_range (char**,int*) ; 

char *get_options(const char *str, int nints, int *ints)
{
	int res, i = 1;

	while (i < nints) {
		res = get_option ((char **)&str, ints + i);
		if (res == 0)
			break;
		if (res == 3) {
			int range_nums;
			range_nums = get_range((char **)&str, ints + i);
			if (range_nums < 0)
				break;
			/*
			 * Decrement the result by one to leave out the
			 * last number in the range.  The next iteration
			 * will handle the upper number in the range
			 */
			i += (range_nums - 1);
		}
		i++;
		if (res == 1)
			break;
	}
	ints[0] = i - 1;
	return (char *)str;
}