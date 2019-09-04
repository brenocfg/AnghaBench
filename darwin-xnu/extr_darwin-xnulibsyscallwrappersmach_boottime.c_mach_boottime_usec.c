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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 scalar_t__ _COMM_PAGE_BOOTTIME_USEC ; 

uint64_t
mach_boottime_usec(void)
{
	return *(uint64_t*)_COMM_PAGE_BOOTTIME_USEC;
}