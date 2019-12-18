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
struct dma_rcv_ctx {int type; int ctx; int num_desc; int buf_size; int split_buf_size; int /*<<< orphan*/  task; scalar_t__ cmdPtr; scalar_t__ ctrlClear; scalar_t__ ctrlSet; int /*<<< orphan*/  lock; int /*<<< orphan*/ ** prg_cpu; int /*<<< orphan*/ * prg_bus; int /*<<< orphan*/ * prg_pool; int /*<<< orphan*/ ** buf_cpu; int /*<<< orphan*/ * buf_bus; int /*<<< orphan*/ * spb; struct ti_ohci* ohci; } ;
struct dma_cmd {int dummy; } ;
typedef  enum context_type { ____Placeholder_context_type } context_type ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 scalar_t__ OHCI1394_ContextCommandPtr ; 
 scalar_t__ OHCI1394_ContextControlClear ; 
 scalar_t__ OHCI1394_ContextControlSet ; 
 int /*<<< orphan*/  PRINT (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  dma_rcv_tasklet ; 
 int /*<<< orphan*/  free_dma_rcv_ctx (struct dma_rcv_ctx*) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * pci_alloc_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pci_pool_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pci_pool_create (char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int
alloc_dma_rcv_ctx(struct ti_ohci *ohci, struct dma_rcv_ctx *d,
		  enum context_type type, int ctx, int num_desc,
		  int buf_size, int split_buf_size, int context_base)
{
	int i, len;
	static int num_allocs;
	static char pool_name[20];

	d->ohci = ohci;
	d->type = type;
	d->ctx = ctx;

	d->num_desc = num_desc;
	d->buf_size = buf_size;
	d->split_buf_size = split_buf_size;

	d->ctrlSet = 0;
	d->ctrlClear = 0;
	d->cmdPtr = 0;

	d->buf_cpu = kzalloc(d->num_desc * sizeof(*d->buf_cpu), GFP_ATOMIC);
	d->buf_bus = kzalloc(d->num_desc * sizeof(*d->buf_bus), GFP_ATOMIC);

	if (d->buf_cpu == NULL || d->buf_bus == NULL) {
		PRINT(KERN_ERR, "Failed to allocate %s", "DMA buffer");
		free_dma_rcv_ctx(d);
		return -ENOMEM;
	}

	d->prg_cpu = kzalloc(d->num_desc * sizeof(*d->prg_cpu), GFP_ATOMIC);
	d->prg_bus = kzalloc(d->num_desc * sizeof(*d->prg_bus), GFP_ATOMIC);

	if (d->prg_cpu == NULL || d->prg_bus == NULL) {
		PRINT(KERN_ERR, "Failed to allocate %s", "DMA prg");
		free_dma_rcv_ctx(d);
		return -ENOMEM;
	}

	d->spb = kmalloc(d->split_buf_size, GFP_ATOMIC);

	if (d->spb == NULL) {
		PRINT(KERN_ERR, "Failed to allocate %s", "split buffer");
		free_dma_rcv_ctx(d);
		return -ENOMEM;
	}
	
	len = sprintf(pool_name, "ohci1394_rcv_prg");
	sprintf(pool_name+len, "%d", num_allocs);
	d->prg_pool = pci_pool_create(pool_name, ohci->dev,
				sizeof(struct dma_cmd), 4, 0);
	if(d->prg_pool == NULL)
	{
		PRINT(KERN_ERR, "pci_pool_create failed for %s", pool_name);
		free_dma_rcv_ctx(d);
		return -ENOMEM;
	}
	num_allocs++;

	for (i=0; i<d->num_desc; i++) {
		d->buf_cpu[i] = pci_alloc_consistent(ohci->dev,
						     d->buf_size,
						     d->buf_bus+i);

		if (d->buf_cpu[i] != NULL) {
			memset(d->buf_cpu[i], 0, d->buf_size);
		} else {
			PRINT(KERN_ERR,
			      "Failed to allocate %s", "DMA buffer");
			free_dma_rcv_ctx(d);
			return -ENOMEM;
		}

		d->prg_cpu[i] = pci_pool_alloc(d->prg_pool, GFP_KERNEL, d->prg_bus+i);

                if (d->prg_cpu[i] != NULL) {
                        memset(d->prg_cpu[i], 0, sizeof(struct dma_cmd));
		} else {
			PRINT(KERN_ERR,
			      "Failed to allocate %s", "DMA prg");
			free_dma_rcv_ctx(d);
			return -ENOMEM;
		}
	}

        spin_lock_init(&d->lock);

	d->ctrlSet = context_base + OHCI1394_ContextControlSet;
	d->ctrlClear = context_base + OHCI1394_ContextControlClear;
	d->cmdPtr = context_base + OHCI1394_ContextCommandPtr;

	tasklet_init(&d->task, dma_rcv_tasklet, (unsigned long) d);
	return 0;
}