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
struct TYPE_4__ {unsigned int num_counters; } ;
struct TYPE_3__ {int /*<<< orphan*/  cnt_lo; int /*<<< orphan*/  cnt_hi; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMCR (int) ; 
 int /*<<< orphan*/  PMCTRH (int) ; 
 int /*<<< orphan*/  PMCTRL (int) ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writew (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ op_model_sh7750_ops ; 
 TYPE_1__* regcache ; 

__attribute__((used)) static void sh7750_ppc_cpu_setup(void *args)
{
	unsigned int counters = op_model_sh7750_ops.num_counters;
	int i;

	for (i = 0; i < counters; i++) {
		__raw_writew(0, PMCR(i));
		__raw_writel(regcache[i].cnt_hi, PMCTRH(i));
		__raw_writel(regcache[i].cnt_lo, PMCTRL(i));
	}
}