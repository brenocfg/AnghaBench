#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long* bits; } ;

/* Variables and functions */
 TYPE_1__* cpu_evtchn_mask_p ; 

__attribute__((used)) static inline unsigned long *cpu_evtchn_mask(int cpu)
{
	return cpu_evtchn_mask_p[cpu].bits;
}