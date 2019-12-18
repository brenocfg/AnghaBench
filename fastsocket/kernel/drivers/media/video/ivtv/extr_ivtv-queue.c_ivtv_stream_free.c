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
struct ivtv_stream {int buf_size; scalar_t__ sg_handle; scalar_t__ sg_processing_size; scalar_t__ sg_pending_size; struct ivtv_buffer* sg_dma; struct ivtv_buffer* sg_processing; struct ivtv_buffer* sg_pending; TYPE_1__* itv; int /*<<< orphan*/  dma; int /*<<< orphan*/  q_free; } ;
struct ivtv_sg_element {int dummy; } ;
struct ivtv_buffer {scalar_t__ dma_handle; struct ivtv_buffer* buf; } ;
struct TYPE_2__ {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 scalar_t__ IVTV_DMA_UNMAPPED ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 struct ivtv_buffer* ivtv_dequeue (struct ivtv_stream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ivtv_flush_queues (struct ivtv_stream*) ; 
 scalar_t__ ivtv_might_use_dma (struct ivtv_stream*) ; 
 int /*<<< orphan*/  kfree (struct ivtv_buffer*) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 

void ivtv_stream_free(struct ivtv_stream *s)
{
	struct ivtv_buffer *buf;

	/* move all buffers to q_free */
	ivtv_flush_queues(s);

	/* empty q_free */
	while ((buf = ivtv_dequeue(s, &s->q_free))) {
		if (ivtv_might_use_dma(s))
			pci_unmap_single(s->itv->pdev, buf->dma_handle,
				s->buf_size + 256, s->dma);
		kfree(buf->buf);
		kfree(buf);
	}

	/* Free SG Array/Lists */
	if (s->sg_dma != NULL) {
		if (s->sg_handle != IVTV_DMA_UNMAPPED) {
			pci_unmap_single(s->itv->pdev, s->sg_handle,
				 sizeof(struct ivtv_sg_element), PCI_DMA_TODEVICE);
			s->sg_handle = IVTV_DMA_UNMAPPED;
		}
		kfree(s->sg_pending);
		kfree(s->sg_processing);
		kfree(s->sg_dma);
		s->sg_pending = NULL;
		s->sg_processing = NULL;
		s->sg_dma = NULL;
		s->sg_pending_size = 0;
		s->sg_processing_size = 0;
	}
}