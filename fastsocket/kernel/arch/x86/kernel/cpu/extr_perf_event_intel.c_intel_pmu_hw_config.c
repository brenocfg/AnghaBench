#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int config; } ;
struct TYPE_5__ {scalar_t__ type; int config; scalar_t__ precise_ip; } ;
struct perf_event {TYPE_1__ hw; TYPE_2__ attr; } ;
struct TYPE_6__ {int version; int /*<<< orphan*/  (* pebs_aliases ) (struct perf_event*) ;} ;

/* Variables and functions */
 int ARCH_PERFMON_EVENTSEL_ANY ; 
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EACCES ; 
 int EINVAL ; 
 scalar_t__ PERF_TYPE_RAW ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 scalar_t__ perf_paranoid_cpu () ; 
 int /*<<< orphan*/  stub1 (struct perf_event*) ; 
 TYPE_3__ x86_pmu ; 
 int x86_pmu_hw_config (struct perf_event*) ; 

__attribute__((used)) static int intel_pmu_hw_config(struct perf_event *event)
{
	int ret = x86_pmu_hw_config(event);

	if (ret)
		return ret;

	if (event->attr.precise_ip && x86_pmu.pebs_aliases)
		x86_pmu.pebs_aliases(event);

	if (event->attr.type != PERF_TYPE_RAW)
		return 0;

	if (!(event->attr.config & ARCH_PERFMON_EVENTSEL_ANY))
		return 0;

	if (x86_pmu.version < 3)
		return -EINVAL;

	if (perf_paranoid_cpu() && !capable(CAP_SYS_ADMIN))
		return -EACCES;

	event->hw.config |= ARCH_PERFMON_EVENTSEL_ANY;

	return 0;
}