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
struct net_device {int dummy; } ;
struct fcoe_interface {int /*<<< orphan*/  removed; struct net_device* netdev; } ;
struct fcoe_ctlr {TYPE_1__* lp; } ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  fcoe_ctlr_destroy (struct fcoe_ctlr*) ; 
 int /*<<< orphan*/  fcoe_interface_remove (struct fcoe_interface*) ; 
 struct fcoe_ctlr* fcoe_to_ctlr (struct fcoe_interface*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  scsi_host_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fcoe_interface_cleanup(struct fcoe_interface *fcoe)
{
	struct net_device *netdev = fcoe->netdev;
	struct fcoe_ctlr *fip = fcoe_to_ctlr(fcoe);

	rtnl_lock();
	if (!fcoe->removed)
		fcoe_interface_remove(fcoe);
	rtnl_unlock();

	/* Release the self-reference taken during fcoe_interface_create() */
	/* tear-down the FCoE controller */
	fcoe_ctlr_destroy(fip);
	scsi_host_put(fip->lp->host);
	dev_put(netdev);
	module_put(THIS_MODULE);
}