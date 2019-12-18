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
struct ub_scsi_cmd_queue {scalar_t__ qlen; scalar_t__ qmax; struct ub_scsi_cmd* head; struct ub_scsi_cmd* tail; } ;
struct ub_scsi_cmd {struct ub_scsi_cmd* next; } ;
struct ub_dev {struct ub_scsi_cmd_queue cmd_queue; } ;

/* Variables and functions */

__attribute__((used)) static void ub_cmdq_insert(struct ub_dev *sc, struct ub_scsi_cmd *cmd)
{
	struct ub_scsi_cmd_queue *t = &sc->cmd_queue;

	if (t->qlen++ == 0) {
		t->head = cmd;
		t->tail = cmd;
	} else {
		cmd->next = t->head;
		t->head = cmd;
	}

	if (t->qlen > t->qmax)
		t->qmax = t->qlen;
}