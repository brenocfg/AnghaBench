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
struct ti_ohci {int /*<<< orphan*/  dev; } ;
struct dma_rcv_ctx {int num_desc; struct ti_ohci* ohci; scalar_t__* spb; scalar_t__* prg_bus; scalar_t__* prg_cpu; int /*<<< orphan*/  prg_pool; scalar_t__* buf_bus; scalar_t__* buf_cpu; int /*<<< orphan*/  buf_size; int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGMSG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pci_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_pool_free (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void free_dma_rcv_ctx(struct dma_rcv_ctx *d)
{
	int i;
	struct ti_ohci *ohci = d->ohci;

	if (ohci == NULL)
		return;

	DBGMSG("Freeing dma_rcv_ctx %d", d->ctx);

	if (d->buf_cpu) {
		for (i=0; i<d->num_desc; i++)
			if (d->buf_cpu[i] && d->buf_bus[i])
				pci_free_consistent(
					ohci->dev, d->buf_size,
					d->buf_cpu[i], d->buf_bus[i]);
		kfree(d->buf_cpu);
		kfree(d->buf_bus);
	}
	if (d->prg_cpu) {
		for (i=0; i<d->num_desc; i++)
			if (d->prg_cpu[i] && d->prg_bus[i])
				pci_pool_free(d->prg_pool, d->prg_cpu[i],
					      d->prg_bus[i]);
		pci_pool_destroy(d->prg_pool);
		kfree(d->prg_cpu);
		kfree(d->prg_bus);
	}
	kfree(d->spb);

	/* Mark this context as freed. */
	d->ohci = NULL;
}