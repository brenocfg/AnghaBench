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
struct fcoe_fcf {scalar_t__ flogi_sent; } ;
struct fcoe_ctlr {int /*<<< orphan*/  ctlr_mutex; int /*<<< orphan*/  ctlr_lock; int /*<<< orphan*/ * flogi_req; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  LIBFCOE_FIP_DBG (struct fcoe_ctlr*,char*) ; 
 int fcoe_ctlr_flogi_send_locked (struct fcoe_ctlr*) ; 
 struct fcoe_fcf* fcoe_ctlr_select (struct fcoe_ctlr*) ; 
 int /*<<< orphan*/  fcoe_ctlr_solicit (struct fcoe_ctlr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fcoe_ctlr_flogi_retry(struct fcoe_ctlr *fip)
{
	struct fcoe_fcf *fcf;
	int error;

	mutex_lock(&fip->ctlr_mutex);
	spin_lock_bh(&fip->ctlr_lock);
	LIBFCOE_FIP_DBG(fip, "re-sending FLOGI - reselect\n");
	fcf = fcoe_ctlr_select(fip);
	if (!fcf || fcf->flogi_sent) {
		kfree_skb(fip->flogi_req);
		fip->flogi_req = NULL;
		error = -ENOENT;
	} else {
		fcoe_ctlr_solicit(fip, NULL);
		error = fcoe_ctlr_flogi_send_locked(fip);
	}
	spin_unlock_bh(&fip->ctlr_lock);
	mutex_unlock(&fip->ctlr_mutex);
	return error;
}