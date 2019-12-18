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
struct fcoe_fcf_device {int /*<<< orphan*/  vlan_id; } ;
struct fcoe_ctlr_device {int dummy; } ;
struct fcoe_ctlr {int dummy; } ;
struct bnx2fc_interface {int /*<<< orphan*/  vlan_id; } ;

/* Variables and functions */
 struct fcoe_ctlr* fcoe_ctlr_device_priv (struct fcoe_ctlr_device*) ; 
 struct bnx2fc_interface* fcoe_ctlr_priv (struct fcoe_ctlr*) ; 
 struct fcoe_ctlr_device* fcoe_fcf_dev_to_ctlr_dev (struct fcoe_fcf_device*) ; 

__attribute__((used)) static void bnx2fc_fcf_get_vlan_id(struct fcoe_fcf_device *fcf_dev)
{
	struct fcoe_ctlr_device *ctlr_dev =
		fcoe_fcf_dev_to_ctlr_dev(fcf_dev);
	struct fcoe_ctlr *ctlr = fcoe_ctlr_device_priv(ctlr_dev);
	struct bnx2fc_interface *fcoe = fcoe_ctlr_priv(ctlr);

	fcf_dev->vlan_id = fcoe->vlan_id;
}