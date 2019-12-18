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
struct rsp_que {struct qla_hw_data* hw; } ;
struct qla_hw_data {TYPE_1__* isp_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* intr_handler ) (int /*<<< orphan*/ ,struct rsp_que*) ;} ;

/* Variables and functions */
 scalar_t__ IS_QLA82XX (struct qla_hw_data*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  qla82xx_poll (int /*<<< orphan*/ ,struct rsp_que*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct rsp_que*) ; 

__attribute__((used)) static inline void
qla2x00_poll(struct rsp_que *rsp)
{
	unsigned long flags;
	struct qla_hw_data *ha = rsp->hw;
	local_irq_save(flags);
	if (IS_QLA82XX(ha))
		qla82xx_poll(0, rsp);
	else
		ha->isp_ops->intr_handler(0, rsp);
	local_irq_restore(flags);
}