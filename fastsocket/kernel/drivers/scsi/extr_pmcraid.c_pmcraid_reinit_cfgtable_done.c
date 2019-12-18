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
struct pmcraid_cmd {TYPE_1__* drv_inst; scalar_t__ release; TYPE_4__* ioa_cb; } ;
struct TYPE_7__ {int /*<<< orphan*/  ioasc; } ;
struct TYPE_6__ {int /*<<< orphan*/ * cdb; } ;
struct TYPE_8__ {TYPE_3__ ioasa; TYPE_2__ ioarcb; } ;
struct TYPE_5__ {int /*<<< orphan*/  worker_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmcraid_info (char*,...) ; 
 int /*<<< orphan*/  pmcraid_return_cmd (struct pmcraid_cmd*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pmcraid_reinit_cfgtable_done(struct pmcraid_cmd *cmd)
{
	pmcraid_info("response internal cmd CDB[0] = %x ioasc = %x\n",
		     cmd->ioa_cb->ioarcb.cdb[0],
		     le32_to_cpu(cmd->ioa_cb->ioasa.ioasc));

	if (cmd->release) {
		cmd->release = 0;
		pmcraid_return_cmd(cmd);
	}
	pmcraid_info("scheduling worker for config table reinitialization\n");
	schedule_work(&cmd->drv_inst->worker_q);
}