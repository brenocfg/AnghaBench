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
struct v4l2_sliced_vbi_format {int io_size; int /*<<< orphan*/  service_set; void*** service_lines; scalar_t__* reserved; } ;
struct v4l2_sliced_vbi_data {int dummy; } ;
struct TYPE_2__ {struct v4l2_sliced_vbi_format sliced; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct ivtv_open_id {struct ivtv* itv; } ;
struct ivtv {int v4l2_cap; scalar_t__ is_60hz; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int V4L2_CAP_SLICED_VBI_OUTPUT ; 
 void* V4L2_SLICED_CAPTION_525 ; 
 void* V4L2_SLICED_VPS ; 
 void* V4L2_SLICED_WSS_625 ; 
 int /*<<< orphan*/  ivtv_get_service_set (struct v4l2_sliced_vbi_format*) ; 

__attribute__((used)) static int ivtv_g_fmt_sliced_vbi_out(struct file *file, void *fh, struct v4l2_format *fmt)
{
	struct ivtv *itv = ((struct ivtv_open_id *)fh)->itv;
	struct v4l2_sliced_vbi_format *vbifmt = &fmt->fmt.sliced;

	vbifmt->reserved[0] = 0;
	vbifmt->reserved[1] = 0;
	if (!(itv->v4l2_cap & V4L2_CAP_SLICED_VBI_OUTPUT))
		return -EINVAL;
	vbifmt->io_size = sizeof(struct v4l2_sliced_vbi_data) * 36;
	if (itv->is_60hz) {
		vbifmt->service_lines[0][21] = V4L2_SLICED_CAPTION_525;
		vbifmt->service_lines[1][21] = V4L2_SLICED_CAPTION_525;
	} else {
		vbifmt->service_lines[0][23] = V4L2_SLICED_WSS_625;
		vbifmt->service_lines[0][16] = V4L2_SLICED_VPS;
	}
	vbifmt->service_set = ivtv_get_service_set(vbifmt);
	return 0;
}