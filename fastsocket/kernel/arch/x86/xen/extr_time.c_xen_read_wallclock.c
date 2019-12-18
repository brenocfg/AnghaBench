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
struct timespec {int dummy; } ;
struct pvclock_wall_clock {int dummy; } ;
struct shared_info {struct pvclock_wall_clock wc; } ;
struct pvclock_vcpu_time_info {int dummy; } ;
struct TYPE_2__ {struct pvclock_vcpu_time_info time; } ;

/* Variables and functions */
 struct shared_info* HYPERVISOR_shared_info ; 
 TYPE_1__* get_cpu_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_cpu_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvclock_read_wallclock (struct pvclock_wall_clock*,struct pvclock_vcpu_time_info*,struct timespec*) ; 
 int /*<<< orphan*/  xen_vcpu ; 

__attribute__((used)) static void xen_read_wallclock(struct timespec *ts)
{
	struct shared_info *s = HYPERVISOR_shared_info;
	struct pvclock_wall_clock *wall_clock = &(s->wc);
        struct pvclock_vcpu_time_info *vcpu_time;

	vcpu_time = &get_cpu_var(xen_vcpu)->time;
	pvclock_read_wallclock(wall_clock, vcpu_time, ts);
	put_cpu_var(xen_vcpu);
}