#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vpif_fh {struct channel_obj* channel; } ;
struct v4l2_pix_format {int sizeimage; int width; int height; } ;
struct TYPE_4__ {struct v4l2_pix_format pix; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct file {int dummy; } ;
struct TYPE_5__ {struct v4l2_pix_format pix; } ;
struct TYPE_6__ {TYPE_2__ fmt; } ;
struct common_obj {TYPE_3__ fmt; } ;
struct channel_obj {struct common_obj* common; } ;

/* Variables and functions */
 size_t VPIF_VIDEO_INDEX ; 
 int vpif_check_format (struct channel_obj*,struct v4l2_pix_format*) ; 

__attribute__((used)) static int vpif_try_fmt_vid_out(struct file *file, void *priv,
				struct v4l2_format *fmt)
{
	struct vpif_fh *fh = priv;
	struct channel_obj *ch = fh->channel;
	struct common_obj *common = &ch->common[VPIF_VIDEO_INDEX];
	struct v4l2_pix_format *pixfmt = &fmt->fmt.pix;
	int ret = 0;

	ret = vpif_check_format(ch, pixfmt);
	if (ret) {
		*pixfmt = common->fmt.fmt.pix;
		pixfmt->sizeimage = pixfmt->width * pixfmt->height * 2;
	}

	return ret;
}