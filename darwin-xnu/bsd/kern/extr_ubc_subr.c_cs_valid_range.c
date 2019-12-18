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
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static boolean_t
cs_valid_range(
	const void *start,
	const void *end,
	const void *lower_bound,
	const void *upper_bound)
{
	if (upper_bound < lower_bound ||
	    end < start) {
		return FALSE;
	}

	if (start < lower_bound ||
	    end > upper_bound) {
		return FALSE;
	}

	return TRUE;
}