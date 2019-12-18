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
struct parport_pc_private {int /*<<< orphan*/  dma_handle; scalar_t__ dma_buf; int /*<<< orphan*/  list; } ;
struct parport_operations {int /*<<< orphan*/  dma_handle; scalar_t__ dma_buf; int /*<<< orphan*/  list; } ;
struct parport {scalar_t__ dma; scalar_t__ irq; int size; int modes; struct parport_pc_private* private_data; TYPE_1__* physport; scalar_t__ base_hi; scalar_t__ base; struct parport_pc_private* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ PARPORT_DMA_NONE ; 
 scalar_t__ PARPORT_IRQ_NONE ; 
 int PARPORT_MODE_ECP ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_dma (scalar_t__) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct parport*) ; 
 int /*<<< orphan*/  kfree (struct parport_pc_private*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parport_put_port (struct parport*) ; 
 int /*<<< orphan*/  parport_remove_port (struct parport*) ; 
 int /*<<< orphan*/  ports_lock ; 
 int /*<<< orphan*/  release_region (scalar_t__,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void parport_pc_unregister_port(struct parport *p)
{
	struct parport_pc_private *priv = p->private_data;
	struct parport_operations *ops = p->ops;

	parport_remove_port(p);
	spin_lock(&ports_lock);
	list_del_init(&priv->list);
	spin_unlock(&ports_lock);
#if defined(CONFIG_PARPORT_PC_FIFO) && defined(HAS_DMA)
	if (p->dma != PARPORT_DMA_NONE)
		free_dma(p->dma);
#endif
	if (p->irq != PARPORT_IRQ_NONE)
		free_irq(p->irq, p);
	release_region(p->base, 3);
	if (p->size > 3)
		release_region(p->base + 3, p->size - 3);
	if (p->modes & PARPORT_MODE_ECP)
		release_region(p->base_hi, 3);
#if defined(CONFIG_PARPORT_PC_FIFO) && defined(HAS_DMA)
	if (priv->dma_buf)
		dma_free_coherent(p->physport->dev, PAGE_SIZE,
				    priv->dma_buf,
				    priv->dma_handle);
#endif
	kfree(p->private_data);
	parport_put_port(p);
	kfree(ops); /* hope no-one cached it */
}