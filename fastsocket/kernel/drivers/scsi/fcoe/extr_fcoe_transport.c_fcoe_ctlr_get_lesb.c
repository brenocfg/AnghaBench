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
struct fcoe_fc_els_lesb {int /*<<< orphan*/  lesb_fcs_error; int /*<<< orphan*/  lesb_err_block; int /*<<< orphan*/  lesb_symb_err; int /*<<< orphan*/  lesb_miss_fka; int /*<<< orphan*/  lesb_vlink_fail; int /*<<< orphan*/  lesb_link_fail; } ;
struct TYPE_2__ {void* lesb_fcs_error; void* lesb_err_block; void* lesb_symb_err; void* lesb_miss_fka; void* lesb_vlink_fail; void* lesb_link_fail; } ;
struct fcoe_ctlr_device {TYPE_1__ lesb; } ;
struct fcoe_ctlr {int /*<<< orphan*/  lp; } ;
struct fc_els_lesb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __fcoe_get_lesb (int /*<<< orphan*/ ,struct fc_els_lesb*,struct net_device*) ; 
 struct fcoe_ctlr* fcoe_ctlr_device_priv (struct fcoe_ctlr_device*) ; 
 struct net_device* fcoe_get_netdev (int /*<<< orphan*/ ) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 

void fcoe_ctlr_get_lesb(struct fcoe_ctlr_device *ctlr_dev)
{
	struct fcoe_ctlr *fip = fcoe_ctlr_device_priv(ctlr_dev);
	struct net_device *netdev = fcoe_get_netdev(fip->lp);
	struct fcoe_fc_els_lesb *fcoe_lesb;
	struct fc_els_lesb fc_lesb;

	__fcoe_get_lesb(fip->lp, &fc_lesb, netdev);
	fcoe_lesb = (struct fcoe_fc_els_lesb *)(&fc_lesb);

	ctlr_dev->lesb.lesb_link_fail =
		ntohl(fcoe_lesb->lesb_link_fail);
	ctlr_dev->lesb.lesb_vlink_fail =
		ntohl(fcoe_lesb->lesb_vlink_fail);
	ctlr_dev->lesb.lesb_miss_fka =
		ntohl(fcoe_lesb->lesb_miss_fka);
	ctlr_dev->lesb.lesb_symb_err =
		ntohl(fcoe_lesb->lesb_symb_err);
	ctlr_dev->lesb.lesb_err_block =
		ntohl(fcoe_lesb->lesb_err_block);
	ctlr_dev->lesb.lesb_fcs_error =
		ntohl(fcoe_lesb->lesb_fcs_error);
}