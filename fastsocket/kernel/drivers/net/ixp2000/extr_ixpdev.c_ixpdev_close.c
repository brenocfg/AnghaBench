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
struct ixpdev_priv {int /*<<< orphan*/  channel; int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_IXP2000_THDA0 ; 
 int /*<<< orphan*/  IXP2000_IRQ_THD_ENABLE_CLEAR_A_0 ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixp2000_reg_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nds ; 
 int /*<<< orphan*/  nds_open ; 
 struct ixpdev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  set_port_admin_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ixpdev_close(struct net_device *dev)
{
	struct ixpdev_priv *ip = netdev_priv(dev);

	netif_stop_queue(dev);
	napi_disable(&ip->napi);
	set_port_admin_status(ip->channel, 0);

	if (!--nds_open) {
		ixp2000_reg_write(IXP2000_IRQ_THD_ENABLE_CLEAR_A_0, 0xffff);
		free_irq(IRQ_IXP2000_THDA0, nds);
	}

	return 0;
}