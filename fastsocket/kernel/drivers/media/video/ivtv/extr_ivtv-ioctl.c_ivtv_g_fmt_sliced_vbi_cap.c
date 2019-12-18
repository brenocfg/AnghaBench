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
struct v4l2_sliced_vbi_format {int io_size; int /*<<< orphan*/  service_set; scalar_t__* reserved; } ;
struct v4l2_sliced_vbi_data {int dummy; } ;
struct TYPE_2__ {struct v4l2_sliced_vbi_format sliced; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct ivtv_open_id {scalar_t__ type; struct ivtv* itv; } ;
struct ivtv {int /*<<< orphan*/  sd_video; scalar_t__ is_50hz; } ;
struct file {int dummy; } ;

/* Variables and functions */
 scalar_t__ IVTV_DEC_STREAM_TYPE_VBI ; 
 int /*<<< orphan*/  V4L2_SLICED_VBI_525 ; 
 int /*<<< orphan*/  V4L2_SLICED_VBI_625 ; 
 int /*<<< orphan*/  g_sliced_fmt ; 
 int /*<<< orphan*/  ivtv_expand_service_set (struct v4l2_sliced_vbi_format*,scalar_t__) ; 
 int /*<<< orphan*/  ivtv_get_service_set (struct v4l2_sliced_vbi_format*) ; 
 int /*<<< orphan*/  v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_sliced_vbi_format*) ; 
 int /*<<< orphan*/  vbi ; 

__attribute__((used)) static int ivtv_g_fmt_sliced_vbi_cap(struct file *file, void *fh, struct v4l2_format *fmt)
{
	struct v4l2_sliced_vbi_format *vbifmt = &fmt->fmt.sliced;
	struct ivtv_open_id *id = fh;
	struct ivtv *itv = id->itv;

	vbifmt->reserved[0] = 0;
	vbifmt->reserved[1] = 0;
	vbifmt->io_size = sizeof(struct v4l2_sliced_vbi_data) * 36;

	if (id->type == IVTV_DEC_STREAM_TYPE_VBI) {
		vbifmt->service_set = itv->is_50hz ? V4L2_SLICED_VBI_625 :
			V4L2_SLICED_VBI_525;
		ivtv_expand_service_set(vbifmt, itv->is_50hz);
		return 0;
	}

	v4l2_subdev_call(itv->sd_video, vbi, g_sliced_fmt, vbifmt);
	vbifmt->service_set = ivtv_get_service_set(vbifmt);
	return 0;
}