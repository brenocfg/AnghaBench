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
struct vpif_fh {struct channel_obj* channel; } ;
struct videobuf_queue {struct vpif_fh* priv_data; } ;
struct videobuf_buffer {int /*<<< orphan*/  state; int /*<<< orphan*/  queue; } ;
struct common_obj {int /*<<< orphan*/  dma_queue; } ;
struct channel_obj {struct common_obj* common; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIDEOBUF_QUEUED ; 
 size_t VPIF_VIDEO_INDEX ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vpif_dbg (int,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void vpif_buffer_queue(struct videobuf_queue *q,
			      struct videobuf_buffer *vb)
{
	/* Get the file handle object and channel object */
	struct vpif_fh *fh = q->priv_data;
	struct channel_obj *ch = fh->channel;
	struct common_obj *common;

	common = &ch->common[VPIF_VIDEO_INDEX];

	vpif_dbg(2, debug, "vpif_buffer_queue\n");

	/* add the buffer to the DMA queue */
	list_add_tail(&vb->queue, &common->dma_queue);
	/* Change state of the buffer */
	vb->state = VIDEOBUF_QUEUED;
}