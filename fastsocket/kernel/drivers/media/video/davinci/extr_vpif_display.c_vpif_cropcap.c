#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vpif_fh {struct channel_obj* channel; } ;
struct TYPE_4__ {int /*<<< orphan*/  width; int /*<<< orphan*/  height; scalar_t__ top; scalar_t__ left; } ;
struct TYPE_3__ {int /*<<< orphan*/  width; int /*<<< orphan*/  height; scalar_t__ top; scalar_t__ left; } ;
struct v4l2_cropcap {scalar_t__ type; TYPE_2__ bounds; TYPE_1__ defrect; } ;
struct file {int dummy; } ;
struct common_obj {int /*<<< orphan*/  width; int /*<<< orphan*/  height; } ;
struct channel_obj {struct common_obj* common; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 size_t VPIF_VIDEO_INDEX ; 

__attribute__((used)) static int vpif_cropcap(struct file *file, void *priv,
			struct v4l2_cropcap *crop)
{
	struct vpif_fh *fh = priv;
	struct channel_obj *ch = fh->channel;
	struct common_obj *common = &ch->common[VPIF_VIDEO_INDEX];
	if (V4L2_BUF_TYPE_VIDEO_OUTPUT != crop->type)
		return -EINVAL;

	crop->bounds.left = crop->bounds.top = 0;
	crop->defrect.left = crop->defrect.top = 0;
	crop->defrect.height = crop->bounds.height = common->height;
	crop->defrect.width = crop->bounds.width = common->width;

	return 0;
}