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
struct op_msrs {TYPE_1__* controls; TYPE_2__* counters; } ;
struct TYPE_6__ {int /*<<< orphan*/  enabled; } ;
struct TYPE_5__ {scalar_t__ addr; } ;
struct TYPE_4__ {scalar_t__ addr; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ MSR_P6_EVNTSEL0 ; 
 scalar_t__ MSR_P6_PERFCTR0 ; 
 TYPE_3__* counter_config ; 
 int num_counters ; 
 int /*<<< orphan*/  op_x86_warn_reserved (int) ; 
 int /*<<< orphan*/  ppro_shutdown (struct op_msrs* const) ; 
 int /*<<< orphan*/  release_perfctr_nmi (scalar_t__) ; 
 int /*<<< orphan*/  reserve_evntsel_nmi (scalar_t__) ; 
 int /*<<< orphan*/  reserve_perfctr_nmi (scalar_t__) ; 

__attribute__((used)) static int ppro_fill_in_addresses(struct op_msrs * const msrs)
{
	int i;

	for (i = 0; i < num_counters; i++) {
		if (!reserve_perfctr_nmi(MSR_P6_PERFCTR0 + i))
			goto fail;
		if (!reserve_evntsel_nmi(MSR_P6_EVNTSEL0 + i)) {
			release_perfctr_nmi(MSR_P6_PERFCTR0 + i);
			goto fail;
		}
		/* both registers must be reserved */
		msrs->counters[i].addr = MSR_P6_PERFCTR0 + i;
		msrs->controls[i].addr = MSR_P6_EVNTSEL0 + i;
		continue;
	fail:
		if (!counter_config[i].enabled)
			continue;
		op_x86_warn_reserved(i);
		ppro_shutdown(msrs);
		return -EBUSY;
	}

	return 0;
}