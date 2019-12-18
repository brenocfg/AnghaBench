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
struct ctlr_info {TYPE_1__* pdev; } ;
struct ErrorInfo {scalar_t__ CommandStatus; } ;
struct CommandList {struct ErrorInfo* err_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  HPSA_DEVICE_RESET_MSG ; 
 int IO_OK ; 
 int /*<<< orphan*/  TYPE_MSG ; 
 struct CommandList* cmd_special_alloc (struct ctlr_info*) ; 
 int /*<<< orphan*/  cmd_special_free (struct ctlr_info*,struct CommandList*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fill_cmd (struct CommandList*,int /*<<< orphan*/ ,struct ctlr_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpsa_scsi_do_simple_cmd_core (struct ctlr_info*,struct CommandList*) ; 
 int /*<<< orphan*/  hpsa_scsi_interpret_error (struct CommandList*) ; 

__attribute__((used)) static int hpsa_send_reset(struct ctlr_info *h, unsigned char *scsi3addr)
{
	int rc = IO_OK;
	struct CommandList *c;
	struct ErrorInfo *ei;

	c = cmd_special_alloc(h);

	if (c == NULL) {			/* trouble... */
		dev_warn(&h->pdev->dev, "cmd_special_alloc returned NULL!\n");
		return -ENOMEM;
	}

	fill_cmd(c, HPSA_DEVICE_RESET_MSG, h, NULL, 0, 0, scsi3addr, TYPE_MSG);
	hpsa_scsi_do_simple_cmd_core(h, c);
	/* no unmap needed here because no data xfer. */

	ei = c->err_info;
	if (ei->CommandStatus != 0) {
		hpsa_scsi_interpret_error(c);
		rc = -1;
	}
	cmd_special_free(h, c);
	return rc;
}