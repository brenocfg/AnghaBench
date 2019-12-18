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
struct dma_buffparms {int max_byte_counter; int neutral_byte; int data_rate; int cfrag; int nbufs; int /*<<< orphan*/  flags; scalar_t__ closing; scalar_t__ mapping_flags; int /*<<< orphan*/  dma_mode; int /*<<< orphan*/  buffsize; int /*<<< orphan*/  bytes_in_use; scalar_t__ byte_counter; scalar_t__ user_counter; scalar_t__ qtail; scalar_t__ qhead; scalar_t__ qlen; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BUSY ; 
 int /*<<< orphan*/  DMODE_NONE ; 

__attribute__((used)) static void dma_init_buffers(struct dma_buffparms *dmap)
{
	dmap->qlen = dmap->qhead = dmap->qtail = dmap->user_counter = 0;
	dmap->byte_counter = 0;
	dmap->max_byte_counter = 8000 * 60 * 60;
	dmap->bytes_in_use = dmap->buffsize;

	dmap->dma_mode = DMODE_NONE;
	dmap->mapping_flags = 0;
	dmap->neutral_byte = 0x80;
	dmap->data_rate = 8000;
	dmap->cfrag = -1;
	dmap->closing = 0;
	dmap->nbufs = 1;
	dmap->flags = DMA_BUSY;	/* Other flags off */
}