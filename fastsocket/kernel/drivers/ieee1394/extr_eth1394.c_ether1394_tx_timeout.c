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
struct hpsb_host {int dummy; } ;
struct eth1394_priv {struct hpsb_host* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH1394_PRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  ether1394_host_reset (struct hpsb_host*) ; 
 scalar_t__ netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ether1394_tx_timeout(struct net_device *dev)
{
	struct hpsb_host *host =
			((struct eth1394_priv *)netdev_priv(dev))->host;

	ETH1394_PRINT(KERN_ERR, dev->name, "Timeout, resetting host\n");
	ether1394_host_reset(host);
}