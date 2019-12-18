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
struct v4l2_vbi_format {int samples_per_line; int sampling_rate; int offset; int* start; int /*<<< orphan*/  flags; void** count; int /*<<< orphan*/  sample_format; } ;
struct TYPE_4__ {struct v4l2_vbi_format vbi; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct TYPE_5__ {int tvnormid; } ;
struct TYPE_6__ {TYPE_2__ context; } ;
struct poseidon {TYPE_3__ video_data; } ;
struct front_face {struct poseidon* pd; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_PIX_FMT_GREY ; 
 int V4L2_STD_525_60 ; 
 int /*<<< orphan*/  V4L2_VBI_UNSYNC ; 
 void* V4L_NTSC_VBI_LINES ; 
 void* V4L_PAL_VBI_LINES ; 
 int /*<<< orphan*/  logs (struct front_face*) ; 

__attribute__((used)) static int vidioc_g_fmt_vbi(struct file *file, void *fh,
			       struct v4l2_format *v4l2_f)
{
	struct front_face *front	= fh;
	struct poseidon *pd		= front->pd;
	struct v4l2_vbi_format *vbi_fmt	= &v4l2_f->fmt.vbi;

	vbi_fmt->samples_per_line	= 720 * 2;
	vbi_fmt->sampling_rate		= 6750000 * 4;
	vbi_fmt->sample_format		= V4L2_PIX_FMT_GREY;
	vbi_fmt->offset			= 64 * 4;  /*FIXME: why offset */
	if (pd->video_data.context.tvnormid & V4L2_STD_525_60) {
		vbi_fmt->start[0] = 10;
		vbi_fmt->start[1] = 264;
		vbi_fmt->count[0] = V4L_NTSC_VBI_LINES;
		vbi_fmt->count[1] = V4L_NTSC_VBI_LINES;
	} else {
		vbi_fmt->start[0] = 6;
		vbi_fmt->start[1] = 314;
		vbi_fmt->count[0] = V4L_PAL_VBI_LINES;
		vbi_fmt->count[1] = V4L_PAL_VBI_LINES;
	}
	vbi_fmt->flags = V4L2_VBI_UNSYNC;
	logs(front);
	return 0;
}