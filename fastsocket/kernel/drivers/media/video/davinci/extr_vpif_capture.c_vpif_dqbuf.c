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
struct v4l2_buffer {int dummy; } ;
struct file {int f_flags; } ;
struct common_obj {int /*<<< orphan*/  buffer_queue; } ;
struct channel_obj {struct common_obj* common; } ;

/* Variables and functions */
 int O_NONBLOCK ; 
 size_t VPIF_VIDEO_INDEX ; 
 int /*<<< orphan*/  debug ; 
 int videobuf_dqbuf (int /*<<< orphan*/ *,struct v4l2_buffer*,int) ; 
 int /*<<< orphan*/  vpif_dbg (int,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int vpif_dqbuf(struct file *file, void *priv, struct v4l2_buffer *buf)
{
	struct vpif_fh *fh = priv;
	struct channel_obj *ch = fh->channel;
	struct common_obj *common = &ch->common[VPIF_VIDEO_INDEX];

	vpif_dbg(2, debug, "vpif_dqbuf\n");

	return videobuf_dqbuf(&common->buffer_queue, buf,
					file->f_flags & O_NONBLOCK);
}