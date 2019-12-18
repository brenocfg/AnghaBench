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
struct net_device {int dummy; } ;
struct fcoe_port {int /*<<< orphan*/  data_src_addr; int /*<<< orphan*/  timer; struct fcoe_interface* priv; } ;
struct fcoe_interface {struct net_device* netdev; } ;
struct fc_lport {int /*<<< orphan*/  host; scalar_t__ vport; } ;

/* Variables and functions */
 int /*<<< orphan*/  FCOE_NETDEV_DBG (struct net_device*,char*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_unicast_delete (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_exch_mgr_free (struct fc_lport*) ; 
 int /*<<< orphan*/  fc_fabric_logoff (struct fc_lport*) ; 
 int /*<<< orphan*/  fc_fcp_destroy (struct fc_lport*) ; 
 int /*<<< orphan*/  fc_lport_destroy (struct fc_lport*) ; 
 int /*<<< orphan*/  fc_lport_free_stats (struct fc_lport*) ; 
 int /*<<< orphan*/  fc_remove_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fcoe_clean_pending_queue (struct fc_lport*) ; 
 int /*<<< orphan*/  fcoe_percpu_clean (struct fc_lport*) ; 
 int /*<<< orphan*/  is_zero_ether_addr (int /*<<< orphan*/ ) ; 
 struct fcoe_port* lport_priv (struct fc_lport*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  scsi_host_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_remove_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fcoe_if_destroy(struct fc_lport *lport)
{
	struct fcoe_port *port = lport_priv(lport);
	struct fcoe_interface *fcoe = port->priv;
	struct net_device *netdev = fcoe->netdev;

	FCOE_NETDEV_DBG(netdev, "Destroying interface\n");

	/* Logout of the fabric */
	fc_fabric_logoff(lport);

	/* Cleanup the fc_lport */
	fc_lport_destroy(lport);

	/* Stop the transmit retry timer */
	del_timer_sync(&port->timer);

	/* Free existing transmit skbs */
	fcoe_clean_pending_queue(lport);

	rtnl_lock();
	if (!is_zero_ether_addr(port->data_src_addr))
		dev_unicast_delete(netdev, port->data_src_addr);
	rtnl_unlock();

	/* Free queued packets for the per-CPU receive threads */
	fcoe_percpu_clean(lport);

	/* Detach from the scsi-ml */
	fc_remove_host(lport->host);
	scsi_remove_host(lport->host);

	/* Destroy lport scsi_priv */
	fc_fcp_destroy(lport);

	/* There are no more rports or I/O, free the EM */
	fc_exch_mgr_free(lport);

	/* Free memory used by statistical counters */
	fc_lport_free_stats(lport);

	/*
	 * Release the Scsi_Host for vport but hold on to
	 * master lport until it fcoe interface fully cleaned-up.
	 */
	if (lport->vport)
		scsi_host_put(lport->host);
}