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
struct TYPE_3__ {int /*<<< orphan*/  address; } ;
struct it_dma_prg {TYPE_1__ end; } ;
struct TYPE_4__ {scalar_t__ kvirt; } ;
struct dma_iso_ctx {int buf_size; int* buffer_prg_assignment; int nb_cmd; int packet_size; TYPE_2__ dma; struct it_dma_prg** it_prg; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_region_offset_to_bus (TYPE_2__*,unsigned long) ; 

__attribute__((used)) static void reprogram_dma_it_prg(struct dma_iso_ctx  *d, int n, int buffer)
{
	struct it_dma_prg *it_prg = d->it_prg[n];
	unsigned long buf = (unsigned long)d->dma.kvirt + buffer * d->buf_size;
	int i;

	d->buffer_prg_assignment[n] = buffer;
	for (i=0;i<d->nb_cmd;i++) {
	  it_prg[i].end.address =
		cpu_to_le32(dma_region_offset_to_bus(&d->dma,
			(buf+i*d->packet_size) - (unsigned long)d->dma.kvirt));
	}
}