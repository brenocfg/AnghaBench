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
struct fcoe_fcf_device {int selected; } ;
struct fcoe_fcf {int dummy; } ;
struct fcoe_ctlr_device {int /*<<< orphan*/  lock; } ;
struct fcoe_ctlr {int /*<<< orphan*/  ctlr_mutex; struct fcoe_fcf* sel_fcf; } ;

/* Variables and functions */
 struct fcoe_ctlr* fcoe_ctlr_device_priv (struct fcoe_ctlr_device*) ; 
 struct fcoe_ctlr_device* fcoe_fcf_dev_to_ctlr_dev (struct fcoe_fcf_device*) ; 
 struct fcoe_fcf* fcoe_fcf_device_priv (struct fcoe_fcf_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void fcoe_fcf_get_selected(struct fcoe_fcf_device *fcf_dev)
{
	struct fcoe_ctlr_device *ctlr_dev = fcoe_fcf_dev_to_ctlr_dev(fcf_dev);
	struct fcoe_ctlr *fip = fcoe_ctlr_device_priv(ctlr_dev);
	struct fcoe_fcf *fcf;

	mutex_lock(&fip->ctlr_mutex);
	mutex_lock(&ctlr_dev->lock);

	fcf = fcoe_fcf_device_priv(fcf_dev);
	if (fcf)
		fcf_dev->selected = (fcf == fip->sel_fcf) ? 1 : 0;
	else
		fcf_dev->selected = 0;

	mutex_unlock(&ctlr_dev->lock);
	mutex_unlock(&fip->ctlr_mutex);
}