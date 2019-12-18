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

__attribute__((used)) static inline void ptr_to_high_low_short(void *ptr, unsigned short *high,
					 unsigned short *low)
{
	*high = (unsigned short)((((unsigned long)ptr) >> 16) & 0xffff);
	*low = (unsigned short)((unsigned long)ptr & 0xffff);
}