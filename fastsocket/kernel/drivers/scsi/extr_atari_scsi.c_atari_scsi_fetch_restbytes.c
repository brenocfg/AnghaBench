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
struct TYPE_2__ {int /*<<< orphan*/  dma_restdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_PRINTK (char*,...) ; 
 unsigned long SCSI_DMA_READ_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_addr ; 
 char* phys_to_virt (unsigned long) ; 
 TYPE_1__ tt_scsi_dma ; 

__attribute__((used)) static void atari_scsi_fetch_restbytes(void)
{
	int nr;
	char *src, *dst;
	unsigned long phys_dst;

	/* fetch rest bytes in the DMA register */
	phys_dst = SCSI_DMA_READ_P(dma_addr);
	nr = phys_dst & 3;
	if (nr) {
		/* there are 'nr' bytes left for the last long address
		   before the DMA pointer */
		phys_dst ^= nr;
		DMA_PRINTK("SCSI DMA: there are %d rest bytes for phys addr 0x%08lx",
			   nr, phys_dst);
		/* The content of the DMA pointer is a physical address!  */
		dst = phys_to_virt(phys_dst);
		DMA_PRINTK(" = virt addr %p\n", dst);
		for (src = (char *)&tt_scsi_dma.dma_restdata; nr != 0; --nr)
			*dst++ = *src++;
	}
}