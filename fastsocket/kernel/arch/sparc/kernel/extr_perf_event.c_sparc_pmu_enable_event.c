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
typedef  int /*<<< orphan*/  u64 ;
struct hw_perf_event {int /*<<< orphan*/  config; } ;
struct cpu_hw_events {int /*<<< orphan*/  pcr; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* write ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mask_for_index (int) ; 
 TYPE_1__* pcr_ops ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void sparc_pmu_enable_event(struct cpu_hw_events *cpuc, struct hw_perf_event *hwc, int idx)
{
	u64 val, mask = mask_for_index(idx);

	val = cpuc->pcr;
	val &= ~mask;
	val |= hwc->config;
	cpuc->pcr = val;

	pcr_ops->write(cpuc->pcr);
}