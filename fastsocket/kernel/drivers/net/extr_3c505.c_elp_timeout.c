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
struct TYPE_2__ {int /*<<< orphan*/  tx_dropped; } ;
struct net_device {TYPE_1__ stats; int /*<<< orphan*/  trans_start; int /*<<< orphan*/  name; int /*<<< orphan*/  base_addr; } ;

/* Variables and functions */
 int ACRF ; 
 int elp_debug ; 
 int inb_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void elp_timeout(struct net_device *dev)
{
	int stat;

	stat = inb_status(dev->base_addr);
	pr_warning("%s: transmit timed out, lost %s?\n", dev->name,
		   (stat & ACRF) ? "interrupt" : "command");
	if (elp_debug >= 1)
		pr_debug("%s: status %#02x\n", dev->name, stat);
	dev->trans_start = jiffies;
	dev->stats.tx_dropped++;
	netif_wake_queue(dev);
}