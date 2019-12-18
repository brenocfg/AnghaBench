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
struct hermes_response {int status; int /*<<< orphan*/  resp2; int /*<<< orphan*/  resp1; int /*<<< orphan*/  resp0; } ;
struct hermes {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* cmd_wait ) (struct hermes*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hermes_response*) ;int /*<<< orphan*/  (* init_cmd_wait ) (struct hermes*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  EVACK ; 
 int HERMES_CMD_DOWNLD ; 
 int HERMES_CMD_INIT ; 
 int /*<<< orphan*/  HERMES_PROGRAM_DISABLE ; 
 int HERMES_STATUS_CMDCODE ; 
 int hermes_aux_control (struct hermes*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hermes_write_regn (struct hermes*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 
 int stub1 (struct hermes*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hermes_response*) ; 
 int /*<<< orphan*/  stub2 (struct hermes*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hermesi_program_end(struct hermes *hw)
{
	struct hermes_response resp;
	int rc = 0;
	int err;

	rc = hw->ops->cmd_wait(hw, HERMES_PROGRAM_DISABLE, 0, &resp);

	pr_debug("PROGRAM_DISABLE returned %d, "
		 "r0 0x%04x, r1 0x%04x, r2 0x%04x\n",
		 rc, resp.resp0, resp.resp1, resp.resp2);

	if ((rc == 0) &&
	    ((resp.status & HERMES_STATUS_CMDCODE) != HERMES_CMD_DOWNLD))
		rc = -EIO;

	err = hermes_aux_control(hw, 0);
	pr_debug("AUX disable returned %d\n", err);

	/* Acknowledge any outstanding command */
	hermes_write_regn(hw, EVACK, 0xFFFF);

	/* Reinitialise, ignoring return */
	(void) hw->ops->init_cmd_wait(hw, 0x0000 | HERMES_CMD_INIT,
				      0, 0, 0, NULL);

	return rc ? rc : err;
}