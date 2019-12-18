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
struct TYPE_2__ {int state; int /*<<< orphan*/  event; } ;
struct dlm_ctxt {TYPE_1__ reco; int /*<<< orphan*/  spinlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DLM_RECO_STATE_ACTIVE ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dlm_end_recovery(struct dlm_ctxt *dlm)
{
	spin_lock(&dlm->spinlock);
	BUG_ON(!(dlm->reco.state & DLM_RECO_STATE_ACTIVE));
	dlm->reco.state &= ~DLM_RECO_STATE_ACTIVE;
	spin_unlock(&dlm->spinlock);
	wake_up(&dlm->reco.event);
}