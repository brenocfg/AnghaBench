#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int size; int /*<<< orphan*/  phys; int /*<<< orphan*/  virt; } ;
struct rio_priv {TYPE_2__ msg_rx_ring; int /*<<< orphan*/  dev; TYPE_1__* msg_regs; } ;
struct rio_mport {struct rio_priv* priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  imr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_RIO_RX (struct rio_mport*) ; 
 int RIO_MAX_MSG_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void rio_close_inb_mbox(struct rio_mport *mport, int mbox)
{
	struct rio_priv *priv = mport->priv;
	/* Disable inbound message unit */
	out_be32(&priv->msg_regs->imr, 0);

	/* Free ring */
	dma_free_coherent(priv->dev, priv->msg_rx_ring.size * RIO_MAX_MSG_SIZE,
			  priv->msg_rx_ring.virt, priv->msg_rx_ring.phys);

	/* Free interrupt */
	free_irq(IRQ_RIO_RX(mport), (void *)mport);
}