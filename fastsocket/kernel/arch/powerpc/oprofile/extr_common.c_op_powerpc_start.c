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
struct TYPE_2__ {int (* global_start ) (int /*<<< orphan*/ ) ;scalar_t__ start; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  ctr ; 
 TYPE_1__* model ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int op_per_cpu_rc ; 
 int /*<<< orphan*/  op_powerpc_cpu_start ; 
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int op_powerpc_start(void)
{
	op_per_cpu_rc = 0;

	if (model->global_start)
		return model->global_start(ctr);
	if (model->start) {
		on_each_cpu(op_powerpc_cpu_start, NULL, 1);
		return op_per_cpu_rc;
	}
	return -EIO; /* No start function is defined for this
			power architecture */
}