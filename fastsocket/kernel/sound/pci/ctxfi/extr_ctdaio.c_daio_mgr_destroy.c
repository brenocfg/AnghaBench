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
struct daio_mgr {int /*<<< orphan*/  mgr; int /*<<< orphan*/  imap_lock; int /*<<< orphan*/  imappers; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_input_mapper_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct daio_mgr*) ; 
 int /*<<< orphan*/  rsc_mgr_uninit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int daio_mgr_destroy(struct daio_mgr *daio_mgr)
{
	unsigned long flags;

	/* free daio input mapper list */
	spin_lock_irqsave(&daio_mgr->imap_lock, flags);
	free_input_mapper_list(&daio_mgr->imappers);
	spin_unlock_irqrestore(&daio_mgr->imap_lock, flags);

	rsc_mgr_uninit(&daio_mgr->mgr);
	kfree(daio_mgr);

	return 0;
}