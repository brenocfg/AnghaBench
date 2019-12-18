#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_7__ {int nr; } ;
struct cpu_hw_events {TYPE_3__ lbr_stack; TYPE_2__* lbr_entries; } ;
typedef  int s64 ;
struct TYPE_5__ {int lbr_format; } ;
struct TYPE_8__ {int lbr_nr; scalar_t__ lbr_to; scalar_t__ lbr_from; TYPE_1__ intel_cap; } ;
struct TYPE_6__ {int from; int to; int mispred; int predicted; scalar_t__ reserved; } ;

/* Variables and functions */
 int LBR_FORMAT_EIP_FLAGS ; 
 int LBR_FROM_FLAG_MISPRED ; 
 int intel_pmu_lbr_tos () ; 
 int /*<<< orphan*/  rdmsrl (scalar_t__,int) ; 
 TYPE_4__ x86_pmu ; 

__attribute__((used)) static void intel_pmu_lbr_read_64(struct cpu_hw_events *cpuc)
{
	unsigned long mask = x86_pmu.lbr_nr - 1;
	int lbr_format = x86_pmu.intel_cap.lbr_format;
	u64 tos = intel_pmu_lbr_tos();
	int i;

	for (i = 0; i < x86_pmu.lbr_nr; i++) {
		unsigned long lbr_idx = (tos - i) & mask;
		u64 from, to, mis = 0, pred = 0;

		rdmsrl(x86_pmu.lbr_from + lbr_idx, from);
		rdmsrl(x86_pmu.lbr_to   + lbr_idx, to);

		if (lbr_format == LBR_FORMAT_EIP_FLAGS) {
			mis = !!(from & LBR_FROM_FLAG_MISPRED);
			pred = !mis;
			from = (u64)((((s64)from) << 1) >> 1);
		}

		cpuc->lbr_entries[i].from	= from;
		cpuc->lbr_entries[i].to		= to;
		cpuc->lbr_entries[i].mispred	= mis;
		cpuc->lbr_entries[i].predicted	= pred;
		cpuc->lbr_entries[i].reserved	= 0;
	}
	cpuc->lbr_stack.nr = i;
}