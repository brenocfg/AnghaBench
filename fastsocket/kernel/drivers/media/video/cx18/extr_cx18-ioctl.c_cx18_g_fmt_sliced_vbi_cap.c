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
struct v4l2_sliced_vbi_format {int io_size; scalar_t__ service_set; scalar_t__* reserved; int /*<<< orphan*/  service_lines; } ;
struct v4l2_sliced_vbi_data {int dummy; } ;
struct TYPE_2__ {struct v4l2_sliced_vbi_format sliced; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct file {int dummy; } ;
struct cx18_open_id {struct cx18* cx; } ;
struct cx18 {int /*<<< orphan*/  sd_av; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ cx18_get_service_set (struct v4l2_sliced_vbi_format*) ; 
 int /*<<< orphan*/  g_sliced_fmt ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_sliced_vbi_format*) ; 
 int /*<<< orphan*/  vbi ; 

__attribute__((used)) static int cx18_g_fmt_sliced_vbi_cap(struct file *file, void *fh,
					struct v4l2_format *fmt)
{
	struct cx18 *cx = ((struct cx18_open_id *)fh)->cx;
	struct v4l2_sliced_vbi_format *vbifmt = &fmt->fmt.sliced;

	/* sane, V4L2 spec compliant, defaults */
	vbifmt->reserved[0] = 0;
	vbifmt->reserved[1] = 0;
	vbifmt->io_size = sizeof(struct v4l2_sliced_vbi_data) * 36;
	memset(vbifmt->service_lines, 0, sizeof(vbifmt->service_lines));
	vbifmt->service_set = 0;

	/*
	 * Fetch the configured service_lines and total service_set from the
	 * digitizer/slicer.  Note, cx18_av_vbi() wipes the passed in
	 * fmt->fmt.sliced under valid calling conditions
	 */
	if (v4l2_subdev_call(cx->sd_av, vbi, g_sliced_fmt, &fmt->fmt.sliced))
		return -EINVAL;

	/* Ensure V4L2 spec compliant output */
	vbifmt->reserved[0] = 0;
	vbifmt->reserved[1] = 0;
	vbifmt->io_size = sizeof(struct v4l2_sliced_vbi_data) * 36;
	vbifmt->service_set = cx18_get_service_set(vbifmt);
	return 0;
}