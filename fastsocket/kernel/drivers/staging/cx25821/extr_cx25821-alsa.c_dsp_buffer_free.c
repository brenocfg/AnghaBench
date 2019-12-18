#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ dma_size; int /*<<< orphan*/ * dma_risc; TYPE_2__* buf; TYPE_4__* pci; } ;
typedef  TYPE_1__ snd_cx25821_card_t ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  risc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  btcx_riscmem_free (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 int /*<<< orphan*/  videobuf_dma_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  videobuf_sg_dma_unmap (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dsp_buffer_free(snd_cx25821_card_t * chip)
{
	BUG_ON(!chip->dma_size);

	dprintk(2, "Freeing buffer\n");
	videobuf_sg_dma_unmap(&chip->pci->dev, chip->dma_risc);
	videobuf_dma_free(chip->dma_risc);
	btcx_riscmem_free(chip->pci, &chip->buf->risc);
	kfree(chip->buf);

	chip->dma_risc = NULL;
	chip->dma_size = 0;

	return 0;
}