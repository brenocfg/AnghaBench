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
struct nic {int /*<<< orphan*/  tx_timeout_task; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct nic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void e100_tx_timeout(struct net_device *netdev)
{
	struct nic *nic = netdev_priv(netdev);

	/* Reset outside of interrupt context, to avoid request_irq
	 * in interrupt context */
	schedule_work(&nic->tx_timeout_task);
}