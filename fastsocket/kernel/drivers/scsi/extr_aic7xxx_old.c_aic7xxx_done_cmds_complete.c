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
struct scsi_cmnd {int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;int /*<<< orphan*/ * host_scribble; } ;
struct TYPE_2__ {struct scsi_cmnd* head; } ;
struct aic7xxx_host {TYPE_1__ completeq; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 

__attribute__((used)) static void aic7xxx_done_cmds_complete(struct aic7xxx_host *p)
{
	struct scsi_cmnd *cmd;

	while (p->completeq.head != NULL) {
		cmd = p->completeq.head;
		p->completeq.head = (struct scsi_cmnd *) cmd->host_scribble;
		cmd->host_scribble = NULL;
		cmd->scsi_done(cmd);
	}
}