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
 long long INT64_MAX ; 
 long long INT64_MIN ; 

__attribute__((used)) static int
dt_ndigits(long long val)
{
	int rval = 1;
	long long cmp = 10;

	if (val < 0) {
		val = val == INT64_MIN ? INT64_MAX : -val;
		rval++;
	}

	while (val > cmp && cmp > 0) {
		rval++;
		cmp *= 10;
	}

	return (rval < 4 ? 4 : rval);
}