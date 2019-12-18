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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 scalar_t__ _COMM_PAGE_APPROX_TIME ; 
 scalar_t__ _COMM_PAGE_APPROX_TIME_SUPPORTED ; 
 int /*<<< orphan*/  mach_absolute_time () ; 

uint64_t mach_approximate_time(void) {
	uint8_t supported = *((uint8_t *)_COMM_PAGE_APPROX_TIME_SUPPORTED);
        if (supported)
        {
            return *((uint64_t *)_COMM_PAGE_APPROX_TIME);
        }
	return mach_absolute_time();
}