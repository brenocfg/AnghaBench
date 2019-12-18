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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct net_device {int mtu; int features; } ;
struct fcoe_port {int /*<<< orphan*/  timer; scalar_t__ fcoe_pending_queue_active; int /*<<< orphan*/  fcoe_pending_queue; struct fcoe_interface* priv; } ;
struct fcoe_interface {int dummy; } ;
struct fcoe_hdr {int dummy; } ;
struct fcoe_ctlr {int /*<<< orphan*/  ctl_src_addr; } ;
struct fcoe_crc_eof {int dummy; } ;
struct fc_lport {int /*<<< orphan*/  vport; } ;

/* Variables and functions */
 int EINVAL ; 
 int FCOE_MTU ; 
 int /*<<< orphan*/  FCOE_NETDEV_DBG (struct net_device*,char*,int) ; 
 int /*<<< orphan*/  NETDEV_FCOE_WWNN ; 
 int /*<<< orphan*/  NETDEV_FCOE_WWPN ; 
 int NETIF_F_FCOE_MTU ; 
 scalar_t__ fc_set_mfs (struct fc_lport*,int) ; 
 int /*<<< orphan*/  fc_set_wwnn (struct fc_lport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_set_wwpn (struct fc_lport*,int /*<<< orphan*/ ) ; 
 scalar_t__ fcoe_get_wwn (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fcoe_link_speed_update (struct fc_lport*) ; 
 int /*<<< orphan*/  fcoe_netdev_features_change (struct fc_lport*,struct net_device*) ; 
 int /*<<< orphan*/  fcoe_queue_timer ; 
 struct fcoe_ctlr* fcoe_to_ctlr (struct fcoe_interface*) ; 
 int /*<<< orphan*/  fcoe_wwn_from_mac (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct fcoe_port* lport_priv (struct fc_lport*) ; 
 int /*<<< orphan*/  setup_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fcoe_netdev_config(struct fc_lport *lport, struct net_device *netdev)
{
	u32 mfs;
	u64 wwnn, wwpn;
	struct fcoe_interface *fcoe;
	struct fcoe_ctlr *ctlr;
	struct fcoe_port *port;

	/* Setup lport private data to point to fcoe softc */
	port = lport_priv(lport);
	fcoe = port->priv;
	ctlr = fcoe_to_ctlr(fcoe);

	/*
	 * Determine max frame size based on underlying device and optional
	 * user-configured limit.  If the MFS is too low, fcoe_link_ok()
	 * will return 0, so do this first.
	 */
	mfs = netdev->mtu;
	if (netdev->features & NETIF_F_FCOE_MTU) {
		mfs = FCOE_MTU;
		FCOE_NETDEV_DBG(netdev, "Supports FCOE_MTU of %d bytes\n", mfs);
	}
	mfs -= (sizeof(struct fcoe_hdr) + sizeof(struct fcoe_crc_eof));
	if (fc_set_mfs(lport, mfs))
		return -EINVAL;

	/* offload features support */
	fcoe_netdev_features_change(lport, netdev);

	skb_queue_head_init(&port->fcoe_pending_queue);
	port->fcoe_pending_queue_active = 0;
	setup_timer(&port->timer, fcoe_queue_timer, (unsigned long)lport);

	fcoe_link_speed_update(lport);

	if (!lport->vport) {
		if (fcoe_get_wwn(netdev, &wwnn, NETDEV_FCOE_WWNN))
			wwnn = fcoe_wwn_from_mac(ctlr->ctl_src_addr, 1, 0);
		fc_set_wwnn(lport, wwnn);
		if (fcoe_get_wwn(netdev, &wwpn, NETDEV_FCOE_WWPN))
			wwpn = fcoe_wwn_from_mac(ctlr->ctl_src_addr,
						 2, 0);
		fc_set_wwpn(lport, wwpn);
	}

	return 0;
}