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
struct common_obj {scalar_t__ memory; } ;
struct channel_obj {size_t channel_id; struct common_obj* common; } ;
struct TYPE_2__ {unsigned int* channel_bufsize; unsigned int min_numbuffers; } ;

/* Variables and functions */
 scalar_t__ V4L2_MEMORY_MMAP ; 
 size_t VPIF_VIDEO_INDEX ; 
 TYPE_1__ config_params ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  vpif_dbg (int,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int vpif_buffer_setup(struct videobuf_queue *q, unsigned int *count,
			     unsigned int *size)
{
	/* Get the file handle object and channel object */
	struct vpif_fh *fh = q->priv_data;
	struct channel_obj *ch = fh->channel;
	struct common_obj *common;

	common = &ch->common[VPIF_VIDEO_INDEX];

	vpif_dbg(2, debug, "vpif_buffer_setup\n");

	/* If memory type is not mmap, return */
	if (V4L2_MEMORY_MMAP != common->memory)
		return 0;

	/* Calculate the size of the buffer */
	*size = config_params.channel_bufsize[ch->channel_id];

	if (*count < config_params.min_numbuffers)
		*count = config_params.min_numbuffers;
	return 0;
}