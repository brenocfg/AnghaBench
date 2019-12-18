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
struct TYPE_2__ {int page_count; int /*<<< orphan*/ * dma_cpu; } ;
struct vino_framebuffer {TYPE_1__ desc_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int VINO_PAGE_RATIO ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*) ; 

__attribute__((used)) static void vino_sync_buffer(struct vino_framebuffer *fb)
{
	int i;

	dprintk("vino_sync_buffer():\n");

	for (i = 0; i < fb->desc_table.page_count; i++)
		dma_sync_single_for_cpu(NULL,
					fb->desc_table.dma_cpu[VINO_PAGE_RATIO * i],
					PAGE_SIZE, DMA_FROM_DEVICE);
}