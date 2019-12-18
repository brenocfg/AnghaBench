#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * next; } ;
struct TYPE_9__ {TYPE_2__ link; } ;
struct dma_iso_ctx {int num_desc; int /*<<< orphan*/  link; struct dma_iso_ctx* next_buffer; struct dma_iso_ctx* last_used_cmd; struct dma_iso_ctx* buffer_time; struct dma_iso_ctx* buffer_prg_assignment; struct dma_iso_ctx* buffer_status; struct dma_iso_ctx* it_prg; struct dma_iso_ctx* ir_prg; struct dma_iso_ctx* prg_reg; int /*<<< orphan*/  dma; TYPE_4__ iso_tasklet; TYPE_3__* ohci; int /*<<< orphan*/  ctrlClear; int /*<<< orphan*/  ctx; } ;
struct TYPE_8__ {TYPE_1__* host; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGMSG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_prog_region_free (struct dma_iso_ctx*) ; 
 int /*<<< orphan*/  dma_region_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct dma_iso_ctx*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ohci1394_stop_context (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ohci1394_unregister_iso_tasklet (TYPE_3__*,TYPE_4__*) ; 

__attribute__((used)) static int free_dma_iso_ctx(struct dma_iso_ctx *d)
{
	int i;

	DBGMSG(d->ohci->host->id, "Freeing dma_iso_ctx %d", d->ctx);

	ohci1394_stop_context(d->ohci, d->ctrlClear, NULL);
	if (d->iso_tasklet.link.next != NULL)
		ohci1394_unregister_iso_tasklet(d->ohci, &d->iso_tasklet);

	dma_region_free(&d->dma);

	if (d->prg_reg) {
		for (i = 0; i < d->num_desc; i++)
			dma_prog_region_free(&d->prg_reg[i]);
		kfree(d->prg_reg);
	}

	kfree(d->ir_prg);
	kfree(d->it_prg);
	kfree(d->buffer_status);
	kfree(d->buffer_prg_assignment);
	kfree(d->buffer_time);
	kfree(d->last_used_cmd);
	kfree(d->next_buffer);
	list_del(&d->link);
	kfree(d);

	return 0;
}