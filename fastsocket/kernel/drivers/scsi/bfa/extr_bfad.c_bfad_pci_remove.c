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
struct pci_dev {int dummy; } ;
struct bfad_s {struct bfad_s* trcmod; int /*<<< orphan*/  list_entry; int /*<<< orphan*/  pport; struct bfad_s* regdata; int /*<<< orphan*/  bfad_lock; int /*<<< orphan*/  bfa; int /*<<< orphan*/ * bfad_tsk; int /*<<< orphan*/  inst_no; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFAD_E_STOP ; 
 int /*<<< orphan*/  bfa_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfad_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (struct bfad_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfad_debugfs_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfad_hal_mem_release (struct bfad_s*) ; 
 int /*<<< orphan*/  bfad_inst ; 
 int /*<<< orphan*/  bfad_mutex ; 
 int /*<<< orphan*/  bfad_pci_uninit (struct pci_dev*,struct bfad_s*) ; 
 int /*<<< orphan*/  kfree (struct bfad_s*) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct bfad_s* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
bfad_pci_remove(struct pci_dev *pdev)
{
	struct bfad_s	      *bfad = pci_get_drvdata(pdev);
	unsigned long	flags;

	bfa_trc(bfad, bfad->inst_no);

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	if (bfad->bfad_tsk != NULL) {
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		kthread_stop(bfad->bfad_tsk);
	} else {
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	}

	/* Send Event BFAD_E_STOP */
	bfa_sm_send_event(bfad, BFAD_E_STOP);

	/* Driver detach and dealloc mem */
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	bfa_detach(&bfad->bfa);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	bfad_hal_mem_release(bfad);

	/* Remove the debugfs node for this bfad */
	kfree(bfad->regdata);
	bfad_debugfs_exit(&bfad->pport);

	/* Cleaning the BFAD instance */
	mutex_lock(&bfad_mutex);
	bfad_inst--;
	list_del(&bfad->list_entry);
	mutex_unlock(&bfad_mutex);
	bfad_pci_uninit(pdev, bfad);

	kfree(bfad->trcmod);
	kfree(bfad);
}