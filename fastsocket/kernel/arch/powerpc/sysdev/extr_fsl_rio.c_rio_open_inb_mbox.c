#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int /*<<< orphan*/ * phys_buffer; int /*<<< orphan*/ * virt_buffer; } ;
struct TYPE_4__ {int size; scalar_t__ phys; int /*<<< orphan*/  virt; int /*<<< orphan*/ ** virt_buffer; scalar_t__ rx_slot; void* dev_id; } ;
struct rio_priv {TYPE_3__* msg_regs; TYPE_2__ msg_tx_ring; int /*<<< orphan*/  dev; TYPE_1__ msg_rx_ring; } ;
struct rio_mport {struct rio_priv* priv; } ;
struct TYPE_6__ {int /*<<< orphan*/  imr; int /*<<< orphan*/  isr; int /*<<< orphan*/  ifqepar; int /*<<< orphan*/  ifqdpar; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQ_RIO_RX (struct rio_mport*) ; 
 int RIO_MAX_MSG_SIZE ; 
 int RIO_MAX_RX_RING_SIZE ; 
 int RIO_MIN_RX_RING_SIZE ; 
 int /*<<< orphan*/  RIO_MSG_BUFFER_SIZE ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ ,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsl_rio_rx_handler ; 
 int get_bitmask_order (int) ; 
 int /*<<< orphan*/  is_power_of_2 (int) ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,int) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,void*) ; 
 int /*<<< orphan*/  setbits32 (int /*<<< orphan*/ *,int) ; 

int rio_open_inb_mbox(struct rio_mport *mport, void *dev_id, int mbox, int entries)
{
	int i, rc = 0;
	struct rio_priv *priv = mport->priv;

	if ((entries < RIO_MIN_RX_RING_SIZE) ||
	    (entries > RIO_MAX_RX_RING_SIZE) || (!is_power_of_2(entries))) {
		rc = -EINVAL;
		goto out;
	}

	/* Initialize client buffer ring */
	priv->msg_rx_ring.dev_id = dev_id;
	priv->msg_rx_ring.size = entries;
	priv->msg_rx_ring.rx_slot = 0;
	for (i = 0; i < priv->msg_rx_ring.size; i++)
		priv->msg_rx_ring.virt_buffer[i] = NULL;

	/* Initialize inbound message ring */
	priv->msg_rx_ring.virt = dma_alloc_coherent(priv->dev,
				priv->msg_rx_ring.size * RIO_MAX_MSG_SIZE,
				&priv->msg_rx_ring.phys, GFP_KERNEL);
	if (!priv->msg_rx_ring.virt) {
		rc = -ENOMEM;
		goto out;
	}

	/* Point dequeue/enqueue pointers at first entry in ring */
	out_be32(&priv->msg_regs->ifqdpar, (u32) priv->msg_rx_ring.phys);
	out_be32(&priv->msg_regs->ifqepar, (u32) priv->msg_rx_ring.phys);

	/* Clear interrupt status */
	out_be32(&priv->msg_regs->isr, 0x00000091);

	/* Hook up inbound message handler */
	rc = request_irq(IRQ_RIO_RX(mport), fsl_rio_rx_handler, 0,
			 "msg_rx", (void *)mport);
	if (rc < 0) {
		dma_free_coherent(priv->dev, RIO_MSG_BUFFER_SIZE,
				  priv->msg_tx_ring.virt_buffer[i],
				  priv->msg_tx_ring.phys_buffer[i]);
		goto out;
	}

	/*
	 * Configure inbound message unit:
	 *      Snooping
	 *      4KB max message size
	 *      Unmask all interrupt sources
	 *      Disable
	 */
	out_be32(&priv->msg_regs->imr, 0x001b0060);

	/* Set number of queue entries */
	setbits32(&priv->msg_regs->imr, (get_bitmask_order(entries) - 2) << 12);

	/* Now enable the unit */
	setbits32(&priv->msg_regs->imr, 0x1);

      out:
	return rc;
}