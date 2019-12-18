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
struct v4l2_sliced_vbi_format {int io_size; scalar_t__ service_set; scalar_t__* reserved; } ;
struct v4l2_sliced_vbi_data {int dummy; } ;
struct TYPE_2__ {struct v4l2_sliced_vbi_format sliced; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct file {int dummy; } ;
struct cx18_open_id {struct cx18* cx; } ;
struct cx18 {int /*<<< orphan*/  is_50hz; } ;

/* Variables and functions */
 scalar_t__ check_service_set (struct v4l2_sliced_vbi_format*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx18_expand_service_set (struct v4l2_sliced_vbi_format*,int /*<<< orphan*/ ) ; 
 scalar_t__ cx18_get_service_set (struct v4l2_sliced_vbi_format*) ; 

__attribute__((used)) static int cx18_try_fmt_sliced_vbi_cap(struct file *file, void *fh,
					struct v4l2_format *fmt)
{
	struct cx18 *cx = ((struct cx18_open_id *)fh)->cx;
	struct v4l2_sliced_vbi_format *vbifmt = &fmt->fmt.sliced;

	vbifmt->io_size = sizeof(struct v4l2_sliced_vbi_data) * 36;
	vbifmt->reserved[0] = 0;
	vbifmt->reserved[1] = 0;

	/* If given a service set, expand it validly & clear passed in set */
	if (vbifmt->service_set)
		cx18_expand_service_set(vbifmt, cx->is_50hz);
	/* Sanitize the service_lines, and compute the new set if any valid */
	if (check_service_set(vbifmt, cx->is_50hz))
		vbifmt->service_set = cx18_get_service_set(vbifmt);
	return 0;
}