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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ TIMER_RESORT_THRESHOLD_ABSTIME ; 
 int /*<<< orphan*/  TRUE ; 

boolean_t
timer_resort_threshold(uint64_t skew) {
	if (skew >= TIMER_RESORT_THRESHOLD_ABSTIME)
		return TRUE;
	else
		return FALSE;
}