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
struct TYPE_2__ {scalar_t__ kvirt; } ;
struct dma_iso_ctx {int buf_size; int* buffer_prg_assignment; int nb_cmd; int left_size; TYPE_1__ dma; struct dma_cmd** ir_prg; } ;
struct dma_cmd {void* address; void* control; } ;

/* Variables and functions */
 int DMA_CTL_BRANCH ; 
 int DMA_CTL_INPUT_MORE ; 
 int DMA_CTL_IRQ ; 
 int DMA_CTL_UPDATE ; 
 int PAGE_SIZE ; 
 void* cpu_to_le32 (int) ; 
 int dma_region_offset_to_bus (TYPE_1__*,unsigned long) ; 

__attribute__((used)) static void reprogram_dma_ir_prg(struct dma_iso_ctx *d, int n, int buffer, int flags)
{
	struct dma_cmd *ir_prg = d->ir_prg[n];
	unsigned long buf = (unsigned long)d->dma.kvirt + buffer * d->buf_size;
	int i;

	d->buffer_prg_assignment[n] = buffer;

	ir_prg[0].address = cpu_to_le32(dma_region_offset_to_bus(&d->dma, buf -
  	                        (unsigned long)d->dma.kvirt));
	ir_prg[1].address = cpu_to_le32(dma_region_offset_to_bus(&d->dma,
				(buf + 4) - (unsigned long)d->dma.kvirt));

	for (i=2;i<d->nb_cmd-1;i++) {
		ir_prg[i].address = cpu_to_le32(dma_region_offset_to_bus(&d->dma,
						(buf+(i-1)*PAGE_SIZE) -
						(unsigned long)d->dma.kvirt));
	}

	ir_prg[i].control = cpu_to_le32(DMA_CTL_INPUT_MORE | DMA_CTL_UPDATE |
				  DMA_CTL_IRQ | DMA_CTL_BRANCH | d->left_size);
	ir_prg[i].address = cpu_to_le32(dma_region_offset_to_bus(&d->dma,
				  (buf+(i-1)*PAGE_SIZE) - (unsigned long)d->dma.kvirt));
}