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
struct ub_scsi_cmd_queue {scalar_t__ qlen; struct ub_scsi_cmd* head; int /*<<< orphan*/ * tail; } ;
struct ub_scsi_cmd {struct ub_scsi_cmd* next; } ;
struct ub_dev {struct ub_scsi_cmd_queue cmd_queue; } ;

/* Variables and functions */

__attribute__((used)) static struct ub_scsi_cmd *ub_cmdq_pop(struct ub_dev *sc)
{
	struct ub_scsi_cmd_queue *t = &sc->cmd_queue;
	struct ub_scsi_cmd *cmd;

	if (t->qlen == 0)
		return NULL;
	if (--t->qlen == 0)
		t->tail = NULL;
	cmd = t->head;
	t->head = cmd->next;
	cmd->next = NULL;
	return cmd;
}