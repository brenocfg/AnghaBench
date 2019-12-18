#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct net_device {int dummy; } ;
struct fcoe_port {int /*<<< orphan*/  timer; scalar_t__ fcoe_pending_queue_active; int /*<<< orphan*/  fcoe_pending_queue; struct bnx2fc_interface* priv; } ;
struct fcoe_ctlr {int /*<<< orphan*/  ctl_src_addr; } ;
struct fc_lport {int /*<<< orphan*/  vport; } ;
struct bnx2fc_interface {struct bnx2fc_hba* hba; } ;
struct bnx2fc_hba {TYPE_2__* phys_dev; } ;
struct TYPE_4__ {TYPE_1__* ethtool_ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  get_pauseparam; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2FC_HBA_DBG (struct fc_lport*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BNX2FC_MFS ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  NETDEV_FCOE_WWNN ; 
 int /*<<< orphan*/  NETDEV_FCOE_WWPN ; 
 struct fcoe_ctlr* bnx2fc_to_ctlr (struct bnx2fc_interface*) ; 
 scalar_t__ fc_set_mfs (struct fc_lport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_set_wwnn (struct fc_lport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_set_wwpn (struct fc_lport*,int /*<<< orphan*/ ) ; 
 scalar_t__ fcoe_get_wwn (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fcoe_link_speed_update (struct fc_lport*) ; 
 int /*<<< orphan*/  fcoe_queue_timer ; 
 int /*<<< orphan*/  fcoe_wwn_from_mac (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct fcoe_port* lport_priv (struct fc_lport*) ; 
 int /*<<< orphan*/  setup_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnx2fc_net_config(struct fc_lport *lport, struct net_device *netdev)
{
	struct bnx2fc_hba *hba;
	struct bnx2fc_interface *interface;
	struct fcoe_ctlr *ctlr;
	struct fcoe_port *port;
	u64 wwnn, wwpn;

	port = lport_priv(lport);
	interface = port->priv;
	ctlr = bnx2fc_to_ctlr(interface);
	hba = interface->hba;

	/* require support for get_pauseparam ethtool op. */
	if (!hba->phys_dev->ethtool_ops ||
	    !hba->phys_dev->ethtool_ops->get_pauseparam)
		return -EOPNOTSUPP;

	if (fc_set_mfs(lport, BNX2FC_MFS))
		return -EINVAL;

	skb_queue_head_init(&port->fcoe_pending_queue);
	port->fcoe_pending_queue_active = 0;
	setup_timer(&port->timer, fcoe_queue_timer, (unsigned long) lport);

	fcoe_link_speed_update(lport);

	if (!lport->vport) {
		if (fcoe_get_wwn(netdev, &wwnn, NETDEV_FCOE_WWNN))
			wwnn = fcoe_wwn_from_mac(ctlr->ctl_src_addr,
						 1, 0);
		BNX2FC_HBA_DBG(lport, "WWNN = 0x%llx\n", wwnn);
		fc_set_wwnn(lport, wwnn);

		if (fcoe_get_wwn(netdev, &wwpn, NETDEV_FCOE_WWPN))
			wwpn = fcoe_wwn_from_mac(ctlr->ctl_src_addr,
						 2, 0);

		BNX2FC_HBA_DBG(lport, "WWPN = 0x%llx\n", wwpn);
		fc_set_wwpn(lport, wwpn);
	}

	return 0;
}