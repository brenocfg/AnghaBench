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
struct w90p910_ether {int rx_packets; int rx_bytes; int /*<<< orphan*/  check_timer; int /*<<< orphan*/  txirq; int /*<<< orphan*/  rxirq; struct platform_device* pdev; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct net_device {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 struct w90p910_ether* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 scalar_t__ request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  w90p910_enable_cam (struct net_device*) ; 
 int /*<<< orphan*/  w90p910_enable_cam_command (struct net_device*) ; 
 int /*<<< orphan*/  w90p910_enable_mac_interrupt (struct net_device*) ; 
 int /*<<< orphan*/  w90p910_enable_rx (struct net_device*,int) ; 
 int /*<<< orphan*/  w90p910_reset_mac (struct net_device*) ; 
 int /*<<< orphan*/  w90p910_rx_interrupt ; 
 int /*<<< orphan*/  w90p910_set_curdest (struct net_device*) ; 
 int /*<<< orphan*/  w90p910_set_fifo_threshold (struct net_device*) ; 
 int /*<<< orphan*/  w90p910_set_global_maccmd (struct net_device*) ; 
 int /*<<< orphan*/  w90p910_trigger_rx (struct net_device*) ; 
 int /*<<< orphan*/  w90p910_tx_interrupt ; 

__attribute__((used)) static int w90p910_ether_open(struct net_device *dev)
{
	struct w90p910_ether *ether;
	struct platform_device *pdev;

	ether = netdev_priv(dev);
	pdev = ether->pdev;

	w90p910_reset_mac(dev);
	w90p910_set_fifo_threshold(dev);
	w90p910_set_curdest(dev);
	w90p910_enable_cam(dev);
	w90p910_enable_cam_command(dev);
	w90p910_enable_mac_interrupt(dev);
	w90p910_set_global_maccmd(dev);
	w90p910_enable_rx(dev, 1);

	ether->rx_packets = 0x0;
	ether->rx_bytes = 0x0;

	if (request_irq(ether->txirq, w90p910_tx_interrupt,
						0x0, pdev->name, dev)) {
		dev_err(&pdev->dev, "register irq tx failed\n");
		return -EAGAIN;
	}

	if (request_irq(ether->rxirq, w90p910_rx_interrupt,
						0x0, pdev->name, dev)) {
		dev_err(&pdev->dev, "register irq rx failed\n");
		free_irq(ether->txirq, dev);
		return -EAGAIN;
	}

	mod_timer(&ether->check_timer, jiffies + msecs_to_jiffies(1000));
	netif_start_queue(dev);
	w90p910_trigger_rx(dev);

	dev_info(&pdev->dev, "%s is OPENED\n", dev->name);

	return 0;
}