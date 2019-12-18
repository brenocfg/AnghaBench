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
struct fcoe_ctlr {scalar_t__ state; int /*<<< orphan*/  lp; int /*<<< orphan*/  ctlr_mutex; } ;

/* Variables and functions */
 scalar_t__ FIP_ST_LINK_WAIT ; 
 int /*<<< orphan*/  LIBFCOE_FIP_DBG (struct fcoe_ctlr*,char*) ; 
 int /*<<< orphan*/  fc_linkdown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fcoe_ctlr_reset (struct fcoe_ctlr*) ; 
 int /*<<< orphan*/  fcoe_ctlr_set_state (struct fcoe_ctlr*,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int fcoe_ctlr_link_down(struct fcoe_ctlr *fip)
{
	int link_dropped;

	LIBFCOE_FIP_DBG(fip, "link down.\n");
	mutex_lock(&fip->ctlr_mutex);
	fcoe_ctlr_reset(fip);
	link_dropped = fip->state != FIP_ST_LINK_WAIT;
	fcoe_ctlr_set_state(fip, FIP_ST_LINK_WAIT);
	mutex_unlock(&fip->ctlr_mutex);

	if (link_dropped)
		fc_linkdown(fip->lp);
	return link_dropped;
}