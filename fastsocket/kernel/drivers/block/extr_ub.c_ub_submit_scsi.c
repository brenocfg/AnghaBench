#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ub_scsi_cmd {scalar_t__ state; scalar_t__ dir; scalar_t__ len; } ;
struct ub_dev {int /*<<< orphan*/  tasklet; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ UB_CMDST_INIT ; 
 scalar_t__ UB_DIR_NONE ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ub_cmdq_add (struct ub_dev*,struct ub_scsi_cmd*) ; 

__attribute__((used)) static int ub_submit_scsi(struct ub_dev *sc, struct ub_scsi_cmd *cmd)
{

	if (cmd->state != UB_CMDST_INIT ||
	    (cmd->dir != UB_DIR_NONE && cmd->len == 0)) {
		return -EINVAL;
	}

	ub_cmdq_add(sc, cmd);
	/*
	 * We can call ub_scsi_dispatch(sc) right away here, but it's a little
	 * safer to jump to a tasklet, in case upper layers do something silly.
	 */
	tasklet_schedule(&sc->tasklet);
	return 0;
}