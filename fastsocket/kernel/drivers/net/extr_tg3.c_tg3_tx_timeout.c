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
struct tg3 {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct tg3* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_msg_tx_err (struct tg3*) ; 
 int /*<<< orphan*/  tg3_dump_state (struct tg3*) ; 
 int /*<<< orphan*/  tg3_reset_task_schedule (struct tg3*) ; 

__attribute__((used)) static void tg3_tx_timeout(struct net_device *dev)
{
	struct tg3 *tp = netdev_priv(dev);

	if (netif_msg_tx_err(tp)) {
		netdev_err(dev, "transmit timed out, resetting\n");
		tg3_dump_state(tp);
	}

	tg3_reset_task_schedule(tp);
}