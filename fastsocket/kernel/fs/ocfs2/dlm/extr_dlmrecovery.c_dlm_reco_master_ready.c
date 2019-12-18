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
struct TYPE_2__ {scalar_t__ new_master; } ;
struct dlm_ctxt {int /*<<< orphan*/  spinlock; TYPE_1__ reco; } ;

/* Variables and functions */
 scalar_t__ O2NM_INVALID_NODE_NUM ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dlm_reco_master_ready(struct dlm_ctxt *dlm)
{
	int ready;
	spin_lock(&dlm->spinlock);
	ready = (dlm->reco.new_master != O2NM_INVALID_NODE_NUM);
	spin_unlock(&dlm->spinlock);
	return ready;
}