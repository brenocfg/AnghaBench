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
struct op_counter_config {int event; int count; int /*<<< orphan*/  enabled; } ;
struct TYPE_4__ {unsigned int num_counters; } ;
struct TYPE_3__ {int ctrl; unsigned long cnt_hi; unsigned long cnt_lo; } ;

/* Variables and functions */
 int PMCR_PMEN ; 
 int PMCR_PMST ; 
 TYPE_2__ op_model_sh7750_ops ; 
 TYPE_1__* regcache ; 

__attribute__((used)) static void sh7750_ppc_reg_setup(struct op_counter_config *ctr)
{
	unsigned int counters = op_model_sh7750_ops.num_counters;
	int i;

	for (i = 0; i < counters; i++) {
		regcache[i].ctrl	= 0;
		regcache[i].cnt_hi	= 0;
		regcache[i].cnt_lo	= 0;

		if (!ctr[i].enabled)
			continue;

		regcache[i].ctrl |= ctr[i].event | PMCR_PMEN | PMCR_PMST;
		regcache[i].cnt_hi = (unsigned long)((ctr->count >> 32) & 0xffff);
		regcache[i].cnt_lo = (unsigned long)(ctr->count & 0xffffffff);
	}
}