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
struct net_device {int /*<<< orphan*/  name; } ;
struct ks_net {int /*<<< orphan*/  lock; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  KS_IER ; 
 int /*<<< orphan*/  KS_ISR ; 
 int /*<<< orphan*/  PMECR_PM_SOFTDOWN ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  ks_disable_qmu (struct ks_net*) ; 
 int /*<<< orphan*/  ks_info (struct ks_net*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ks_set_powermode (struct ks_net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ks_wrreg16 (struct ks_net*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ks_net* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_msg_ifdown (struct ks_net*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 

__attribute__((used)) static int ks_net_stop(struct net_device *netdev)
{
	struct ks_net *ks = netdev_priv(netdev);

	if (netif_msg_ifdown(ks))
		ks_info(ks, "%s: shutting down\n", netdev->name);

	netif_stop_queue(netdev);

	mutex_lock(&ks->lock);

	/* turn off the IRQs and ack any outstanding */
	ks_wrreg16(ks, KS_IER, 0x0000);
	ks_wrreg16(ks, KS_ISR, 0xffff);

	/* shutdown RX/TX QMU */
	ks_disable_qmu(ks);

	/* set powermode to soft power down to save power */
	ks_set_powermode(ks, PMECR_PM_SOFTDOWN);
	free_irq(ks->irq, netdev);
	mutex_unlock(&ks->lock);
	return 0;
}