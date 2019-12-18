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
struct TYPE_2__ {int page_count; scalar_t__* virtual; int /*<<< orphan*/  dma; int /*<<< orphan*/ * dma_cpu; } ;
struct vino_framebuffer {TYPE_1__ desc_table; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageReserved (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 unsigned int VINO_PAGE_RATIO ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,unsigned int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,unsigned int) ; 
 int /*<<< orphan*/  free_page (scalar_t__) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 int /*<<< orphan*/  memset (struct vino_framebuffer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  virt_to_page (void*) ; 

__attribute__((used)) static void vino_free_buffer_with_count(struct vino_framebuffer *fb,
					       unsigned int count)
{
	unsigned int i;

	dprintk("vino_free_buffer_with_count(): count = %d\n", count);

	for (i = 0; i < count; i++) {
		ClearPageReserved(virt_to_page((void *)fb->desc_table.virtual[i]));
		dma_unmap_single(NULL,
				 fb->desc_table.dma_cpu[VINO_PAGE_RATIO * i],
				 PAGE_SIZE, DMA_FROM_DEVICE);
		free_page(fb->desc_table.virtual[i]);
	}

	dma_free_coherent(NULL,
			  VINO_PAGE_RATIO * (fb->desc_table.page_count + 4) *
			  sizeof(dma_addr_t), (void *)fb->desc_table.dma_cpu,
			  fb->desc_table.dma);
	kfree(fb->desc_table.virtual);

	memset(fb, 0, sizeof(struct vino_framebuffer));
}