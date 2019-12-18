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
struct vpif_fh {struct channel_obj* channel; } ;
struct videobuf_queue {struct vpif_fh* priv_data; } ;
struct videobuf_buffer {int /*<<< orphan*/  state; } ;
struct common_obj {scalar_t__ memory; } ;
struct channel_obj {size_t channel_id; struct common_obj* common; } ;
struct TYPE_2__ {unsigned int* channel_bufsize; } ;

/* Variables and functions */
 scalar_t__ V4L2_MEMORY_MMAP ; 
 int /*<<< orphan*/  VIDEOBUF_NEEDS_INIT ; 
 size_t VPIF_VIDEO_INDEX ; 
 TYPE_1__ config_params ; 
 int /*<<< orphan*/  videobuf_dma_contig_free (struct videobuf_queue*,struct videobuf_buffer*) ; 

__attribute__((used)) static void vpif_buffer_release(struct videobuf_queue *q,
				struct videobuf_buffer *vb)
{
	struct vpif_fh *fh = q->priv_data;
	struct channel_obj *ch = fh->channel;
	struct common_obj *common;
	unsigned int buf_size = 0;

	common = &ch->common[VPIF_VIDEO_INDEX];

	videobuf_dma_contig_free(q, vb);
	vb->state = VIDEOBUF_NEEDS_INIT;

	if (V4L2_MEMORY_MMAP != common->memory)
		return;

	buf_size = config_params.channel_bufsize[ch->channel_id];
}