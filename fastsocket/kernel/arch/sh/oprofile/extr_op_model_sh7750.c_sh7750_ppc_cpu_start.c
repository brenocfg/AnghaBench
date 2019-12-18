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
struct TYPE_3__ {int /*<<< orphan*/  ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMCR (int) ; 
 int /*<<< orphan*/  __raw_writew (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ op_model_sh7750_ops ; 
 TYPE_1__* regcache ; 

__attribute__((used)) static void sh7750_ppc_cpu_start(void *args)
{
	unsigned int counters = op_model_sh7750_ops.num_counters;
	int i;

	for (i = 0; i < counters; i++)
		__raw_writew(regcache[i].ctrl, PMCR(i));
}