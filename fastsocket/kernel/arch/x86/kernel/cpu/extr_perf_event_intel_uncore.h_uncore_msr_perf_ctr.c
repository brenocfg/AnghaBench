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
struct intel_uncore_box {TYPE_2__* pmu; } ;
struct TYPE_4__ {TYPE_1__* type; } ;
struct TYPE_3__ {int perf_ctr; scalar_t__ pair_ctr_ctl; } ;

/* Variables and functions */
 int uncore_msr_box_offset (struct intel_uncore_box*) ; 

__attribute__((used)) static inline
unsigned uncore_msr_perf_ctr(struct intel_uncore_box *box, int idx)
{
	return box->pmu->type->perf_ctr +
		(box->pmu->type->pair_ctr_ctl ? 2 * idx : idx) +
		uncore_msr_box_offset(box);
}