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
struct pvclock_vcpu_time_info {int dummy; } ;
typedef  int /*<<< orphan*/  cycle_t ;
struct TYPE_2__ {struct pvclock_vcpu_time_info time; } ;

/* Variables and functions */
 TYPE_1__* get_cpu_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_cpu_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvclock_clocksource_read (struct pvclock_vcpu_time_info*) ; 
 int /*<<< orphan*/  xen_vcpu ; 

cycle_t xen_clocksource_read(void)
{
        struct pvclock_vcpu_time_info *src;
	cycle_t ret;

	src = &get_cpu_var(xen_vcpu)->time;
	ret = pvclock_clocksource_read(src);
	put_cpu_var(xen_vcpu);
	return ret;
}