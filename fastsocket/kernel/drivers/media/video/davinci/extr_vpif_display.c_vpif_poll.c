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
struct file {struct vpif_fh* private_data; } ;
struct common_obj {int /*<<< orphan*/  buffer_queue; scalar_t__ started; } ;
struct channel_obj {struct common_obj* common; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 size_t VPIF_VIDEO_INDEX ; 
 unsigned int videobuf_poll_stream (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int vpif_poll(struct file *filep, poll_table *wait)
{
	struct vpif_fh *fh = filep->private_data;
	struct channel_obj *ch = fh->channel;
	struct common_obj *common = &ch->common[VPIF_VIDEO_INDEX];

	if (common->started)
		return videobuf_poll_stream(filep, &common->buffer_queue, wait);

	return 0;
}