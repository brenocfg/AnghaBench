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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  global_alpha; int /*<<< orphan*/  chromakey; } ;
struct TYPE_4__ {TYPE_1__ win; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct ivtv_open_id {struct ivtv* itv; } ;
struct ivtv {int v4l2_cap; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int V4L2_CAP_VIDEO_OUTPUT ; 
 int /*<<< orphan*/  ivtv_g_fmt_vid_out_overlay (struct file*,void*,struct v4l2_format*) ; 

__attribute__((used)) static int ivtv_try_fmt_vid_out_overlay(struct file *file, void *fh, struct v4l2_format *fmt)
{
	struct ivtv *itv = ((struct ivtv_open_id *)fh)->itv;
	u32 chromakey = fmt->fmt.win.chromakey;
	u8 global_alpha = fmt->fmt.win.global_alpha;

	if (!(itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT))
		return -EINVAL;
	ivtv_g_fmt_vid_out_overlay(file, fh, fmt);
	fmt->fmt.win.chromakey = chromakey;
	fmt->fmt.win.global_alpha = global_alpha;
	return 0;
}