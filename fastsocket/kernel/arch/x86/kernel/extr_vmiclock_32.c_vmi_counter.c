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
typedef  int u32 ;

/* Variables and functions */
 int VMI_ALARM_COUNTER_MASK ; 

__attribute__((used)) static inline u32 vmi_counter(u32 flags)
{
	/* Given VMI_ONESHOT or VMI_PERIODIC, return the corresponding
	 * cycle counter. */
	return flags & VMI_ALARM_COUNTER_MASK;
}