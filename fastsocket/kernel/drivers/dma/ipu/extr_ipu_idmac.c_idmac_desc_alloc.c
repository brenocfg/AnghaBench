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
struct dma_async_tx_descriptor {int /*<<< orphan*/  tx_submit; } ;
struct idmac_tx_desc {int /*<<< orphan*/  list; struct dma_async_tx_descriptor txd; } ;
struct TYPE_4__ {int /*<<< orphan*/  device; } ;
struct idmac_channel {int n_tx_desc; int /*<<< orphan*/  free_list; TYPE_2__ dma_chan; int /*<<< orphan*/  queue; struct idmac_tx_desc* desc; } ;
struct idmac {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  tasklet; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_async_tx_descriptor_init (struct dma_async_tx_descriptor*,TYPE_2__*) ; 
 int /*<<< orphan*/  idmac_tx_submit ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct dma_async_tx_descriptor*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_enable (int /*<<< orphan*/ *) ; 
 struct idmac* to_idmac (int /*<<< orphan*/ ) ; 
 TYPE_1__* to_ipu (struct idmac*) ; 
 struct idmac_tx_desc* vmalloc (int) ; 

__attribute__((used)) static int idmac_desc_alloc(struct idmac_channel *ichan, int n)
{
	struct idmac_tx_desc *desc = vmalloc(n * sizeof(struct idmac_tx_desc));
	struct idmac *idmac = to_idmac(ichan->dma_chan.device);

	if (!desc)
		return -ENOMEM;

	/* No interrupts, just disable the tasklet for a moment */
	tasklet_disable(&to_ipu(idmac)->tasklet);

	ichan->n_tx_desc = n;
	ichan->desc = desc;
	INIT_LIST_HEAD(&ichan->queue);
	INIT_LIST_HEAD(&ichan->free_list);

	while (n--) {
		struct dma_async_tx_descriptor *txd = &desc->txd;

		memset(txd, 0, sizeof(*txd));
		dma_async_tx_descriptor_init(txd, &ichan->dma_chan);
		txd->tx_submit		= idmac_tx_submit;

		list_add(&desc->list, &ichan->free_list);

		desc++;
	}

	tasklet_enable(&to_ipu(idmac)->tasklet);

	return 0;
}