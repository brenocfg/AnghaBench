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
struct videobuf_queue {int /*<<< orphan*/  dev; } ;
struct videobuf_dma_sg_memory {int /*<<< orphan*/  dma; int /*<<< orphan*/  magic; } ;
struct videobuf_buffer {int memory; int /*<<< orphan*/  size; scalar_t__ boff; int /*<<< orphan*/  bsize; int /*<<< orphan*/  baddr; struct videobuf_dma_sg_memory* priv; } ;
struct v4l2_framebuffer {scalar_t__ base; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int EINVAL ; 
 int /*<<< orphan*/  MAGIC_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAGIC_SG_MEM ; 
 int PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 int PAGE_SHIFT ; 
#define  V4L2_MEMORY_MMAP 130 
#define  V4L2_MEMORY_OVERLAY 129 
#define  V4L2_MEMORY_USERPTR 128 
 int videobuf_dma_init_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int videobuf_dma_init_overlay (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int videobuf_dma_init_user (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int videobuf_dma_init_user_locked (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int videobuf_dma_map (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __videobuf_iolock(struct videobuf_queue *q,
			     struct videobuf_buffer *vb,
			     struct v4l2_framebuffer *fbuf)
{
	int err, pages;
	dma_addr_t bus;
	struct videobuf_dma_sg_memory *mem = vb->priv;
	BUG_ON(!mem);

	MAGIC_CHECK(mem->magic, MAGIC_SG_MEM);

	switch (vb->memory) {
	case V4L2_MEMORY_MMAP:
	case V4L2_MEMORY_USERPTR:
		if (0 == vb->baddr) {
			/* no userspace addr -- kernel bounce buffer */
			pages = PAGE_ALIGN(vb->size) >> PAGE_SHIFT;
			err = videobuf_dma_init_kernel(&mem->dma,
						       DMA_FROM_DEVICE,
						       pages);
			if (0 != err)
				return err;
		} else if (vb->memory == V4L2_MEMORY_USERPTR) {
			/* dma directly to userspace */
			err = videobuf_dma_init_user(&mem->dma,
						     DMA_FROM_DEVICE,
						     vb->baddr, vb->bsize);
			if (0 != err)
				return err;
		} else {
			/* NOTE: HACK: videobuf_iolock on V4L2_MEMORY_MMAP
			buffers can only be called from videobuf_qbuf
			we take current->mm->mmap_sem there, to prevent
			locking inversion, so don't take it here */

			err = videobuf_dma_init_user_locked(&mem->dma,
						      DMA_FROM_DEVICE,
						      vb->baddr, vb->bsize);
			if (0 != err)
				return err;
		}
		break;
	case V4L2_MEMORY_OVERLAY:
		if (NULL == fbuf)
			return -EINVAL;
		/* FIXME: need sanity checks for vb->boff */
		/*
		 * Using a double cast to avoid compiler warnings when
		 * building for PAE. Compiler doesn't like direct casting
		 * of a 32 bit ptr to 64 bit integer.
		 */
		bus   = (dma_addr_t)(unsigned long)fbuf->base + vb->boff;
		pages = PAGE_ALIGN(vb->size) >> PAGE_SHIFT;
		err = videobuf_dma_init_overlay(&mem->dma, DMA_FROM_DEVICE,
						bus, pages);
		if (0 != err)
			return err;
		break;
	default:
		BUG();
	}
	err = videobuf_dma_map(q->dev, &mem->dma);
	if (0 != err)
		return err;

	return 0;
}