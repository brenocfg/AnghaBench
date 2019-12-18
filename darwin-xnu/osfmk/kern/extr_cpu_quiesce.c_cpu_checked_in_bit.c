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
typedef  unsigned long checkin_mask_t ;

/* Variables and functions */

__attribute__((used)) static inline checkin_mask_t
cpu_checked_in_bit(int cpuid)
{
	return 1UL << (2 * cpuid);
}