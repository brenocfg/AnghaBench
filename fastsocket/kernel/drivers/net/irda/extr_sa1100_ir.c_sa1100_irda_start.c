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
struct sa1100_irda {int speed; int open; int /*<<< orphan*/  rxdma; int /*<<< orphan*/  txdma; int /*<<< orphan*/  irlap; int /*<<< orphan*/  qos; } ;
struct net_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_Ser2HSSPRd ; 
 int /*<<< orphan*/  DMA_Ser2HSSPWr ; 
 int ENOMEM ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  irlap_open (struct net_device*,int /*<<< orphan*/ *,char*) ; 
 struct sa1100_irda* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  power_level ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  sa1100_free_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sa1100_irda_irq ; 
 int /*<<< orphan*/  sa1100_irda_shutdown (struct sa1100_irda*) ; 
 int sa1100_irda_startup (struct sa1100_irda*) ; 
 int /*<<< orphan*/ * sa1100_irda_txdma_irq ; 
 int sa1100_request_dma (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sa1100_set_power (struct sa1100_irda*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sa1100_irda_start(struct net_device *dev)
{
	struct sa1100_irda *si = netdev_priv(dev);
	int err;

	si->speed = 9600;

	err = request_irq(dev->irq, sa1100_irda_irq, 0, dev->name, dev);
	if (err)
		goto err_irq;

	err = sa1100_request_dma(DMA_Ser2HSSPRd, "IrDA receive",
				 NULL, NULL, &si->rxdma);
	if (err)
		goto err_rx_dma;

	err = sa1100_request_dma(DMA_Ser2HSSPWr, "IrDA transmit",
				 sa1100_irda_txdma_irq, dev, &si->txdma);
	if (err)
		goto err_tx_dma;

	/*
	 * The interrupt must remain disabled for now.
	 */
	disable_irq(dev->irq);

	/*
	 * Setup the serial port for the specified speed.
	 */
	err = sa1100_irda_startup(si);
	if (err)
		goto err_startup;

	/*
	 * Open a new IrLAP layer instance.
	 */
	si->irlap = irlap_open(dev, &si->qos, "sa1100");
	err = -ENOMEM;
	if (!si->irlap)
		goto err_irlap;

	/*
	 * Now enable the interrupt and start the queue
	 */
	si->open = 1;
	sa1100_set_power(si, power_level); /* low power mode */
	enable_irq(dev->irq);
	netif_start_queue(dev);
	return 0;

err_irlap:
	si->open = 0;
	sa1100_irda_shutdown(si);
err_startup:
	sa1100_free_dma(si->txdma);
err_tx_dma:
	sa1100_free_dma(si->rxdma);
err_rx_dma:
	free_irq(dev->irq, dev);
err_irq:
	return err;
}