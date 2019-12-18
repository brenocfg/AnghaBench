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
struct vm_area_struct {int /*<<< orphan*/  vm_end; int /*<<< orphan*/  vm_start; struct videobuf_mapping* vm_private_data; } ;
struct videobuf_queue {int /*<<< orphan*/  vb_lock; TYPE_1__** bufs; int /*<<< orphan*/  dev; scalar_t__ streaming; } ;
struct videobuf_mapping {scalar_t__ count; struct videobuf_queue* q; } ;
struct videobuf_dma_contig_memory {int /*<<< orphan*/ * vaddr; int /*<<< orphan*/  dma_handle; int /*<<< orphan*/  size; int /*<<< orphan*/  magic; } ;
struct TYPE_2__ {scalar_t__ baddr; struct videobuf_mapping* map; struct videobuf_dma_contig_memory* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAGIC_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAGIC_DC_MEM ; 
 int VIDEO_MAX_FRAME ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct videobuf_mapping*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  videobuf_queue_cancel (struct videobuf_queue*) ; 

__attribute__((used)) static void videobuf_vm_close(struct vm_area_struct *vma)
{
	struct videobuf_mapping *map = vma->vm_private_data;
	struct videobuf_queue *q = map->q;
	int i;

	dev_dbg(map->q->dev, "vm_close %p [count=%u,vma=%08lx-%08lx]\n",
		map, map->count, vma->vm_start, vma->vm_end);

	map->count--;
	if (0 == map->count) {
		struct videobuf_dma_contig_memory *mem;

		dev_dbg(map->q->dev, "munmap %p q=%p\n", map, q);
		mutex_lock(&q->vb_lock);

		/* We need first to cancel streams, before unmapping */
		if (q->streaming)
			videobuf_queue_cancel(q);

		for (i = 0; i < VIDEO_MAX_FRAME; i++) {
			if (NULL == q->bufs[i])
				continue;

			if (q->bufs[i]->map != map)
				continue;

			mem = q->bufs[i]->priv;
			if (mem) {
				/* This callback is called only if kernel has
				   allocated memory and this memory is mmapped.
				   In this case, memory should be freed,
				   in order to do memory unmap.
				 */

				MAGIC_CHECK(mem->magic, MAGIC_DC_MEM);

				/* vfree is not atomic - can't be
				   called with IRQ's disabled
				 */
				dev_dbg(map->q->dev, "buf[%d] freeing %p\n",
					i, mem->vaddr);

				dma_free_coherent(q->dev, mem->size,
						  mem->vaddr, mem->dma_handle);
				mem->vaddr = NULL;
			}

			q->bufs[i]->map   = NULL;
			q->bufs[i]->baddr = 0;
		}

		kfree(map);

		mutex_unlock(&q->vb_lock);
	}
}