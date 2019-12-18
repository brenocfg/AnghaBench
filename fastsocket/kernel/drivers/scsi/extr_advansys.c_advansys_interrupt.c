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
struct TYPE_2__ {int /*<<< orphan*/  adv_dvc_var; int /*<<< orphan*/  asc_dvc_var; } ;
struct asc_board {TYPE_1__ dvc_var; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; int /*<<< orphan*/  io_port; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASC_DBG (int,char*,...) ; 
 scalar_t__ ASC_NARROW_BOARD (struct asc_board*) ; 
 int /*<<< orphan*/  ASC_STATS (struct Scsi_Host*,int /*<<< orphan*/ ) ; 
 scalar_t__ AdvISR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AscISR (int /*<<< orphan*/ *) ; 
 scalar_t__ AscIsIntPending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  interrupt ; 
 struct asc_board* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t advansys_interrupt(int irq, void *dev_id)
{
	struct Scsi_Host *shost = dev_id;
	struct asc_board *boardp = shost_priv(shost);
	irqreturn_t result = IRQ_NONE;

	ASC_DBG(2, "boardp 0x%p\n", boardp);
	spin_lock(shost->host_lock);
	if (ASC_NARROW_BOARD(boardp)) {
		if (AscIsIntPending(shost->io_port)) {
			result = IRQ_HANDLED;
			ASC_STATS(shost, interrupt);
			ASC_DBG(1, "before AscISR()\n");
			AscISR(&boardp->dvc_var.asc_dvc_var);
		}
	} else {
		ASC_DBG(1, "before AdvISR()\n");
		if (AdvISR(&boardp->dvc_var.adv_dvc_var)) {
			result = IRQ_HANDLED;
			ASC_STATS(shost, interrupt);
		}
	}
	spin_unlock(shost->host_lock);

	ASC_DBG(1, "end\n");
	return result;
}