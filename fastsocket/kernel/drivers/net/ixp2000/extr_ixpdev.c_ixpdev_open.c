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
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  IRQ_IXP2000_THDA0 ; 
 int /*<<< orphan*/  IXP2000_IRQ_THD_ENABLE_SET_A_0 ; 
 int /*<<< orphan*/  ixp2000_reg_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ixpdev_interrupt ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nds ; 
 int /*<<< orphan*/  nds_open ; 
 struct ixpdev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_port_admin_status (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ixpdev_open(struct net_device *dev)
{
	struct ixpdev_priv *ip = netdev_priv(dev);
	int err;

	napi_enable(&ip->napi);
	if (!nds_open++) {
		err = request_irq(IRQ_IXP2000_THDA0, ixpdev_interrupt,
					IRQF_SHARED, "ixp2000_eth", nds);
		if (err) {
			nds_open--;
			napi_disable(&ip->napi);
			return err;
		}

		ixp2000_reg_write(IXP2000_IRQ_THD_ENABLE_SET_A_0, 0xffff);
	}

	set_port_admin_status(ip->channel, 1);
	netif_start_queue(dev);

	return 0;
}