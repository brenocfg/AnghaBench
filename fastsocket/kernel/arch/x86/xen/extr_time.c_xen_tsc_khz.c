#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pvclock_vcpu_time_info {int dummy; } ;
struct TYPE_4__ {TYPE_1__* vcpu_info; } ;
struct TYPE_3__ {struct pvclock_vcpu_time_info time; } ;

/* Variables and functions */
 TYPE_2__* HYPERVISOR_shared_info ; 
 unsigned long pvclock_tsc_khz (struct pvclock_vcpu_time_info*) ; 

unsigned long xen_tsc_khz(void)
{
	struct pvclock_vcpu_time_info *info =
		&HYPERVISOR_shared_info->vcpu_info[0].time;

	return pvclock_tsc_khz(info);
}