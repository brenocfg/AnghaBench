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
struct v4l2_vbi_format {int sampling_rate; int offset; scalar_t__* reserved; scalar_t__ flags; int /*<<< orphan*/ * count; int /*<<< orphan*/ * start; int /*<<< orphan*/  sample_format; scalar_t__ samples_per_line; } ;
struct TYPE_3__ {struct v4l2_vbi_format vbi; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct file {int dummy; } ;
struct cx18_open_id {struct cx18* cx; } ;
struct TYPE_4__ {int /*<<< orphan*/  count; int /*<<< orphan*/ * start; } ;
struct cx18 {TYPE_2__ vbi; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_PIX_FMT_GREY ; 
 scalar_t__ vbi_active_samples ; 

__attribute__((used)) static int cx18_g_fmt_vbi_cap(struct file *file, void *fh,
				struct v4l2_format *fmt)
{
	struct cx18 *cx = ((struct cx18_open_id *)fh)->cx;
	struct v4l2_vbi_format *vbifmt = &fmt->fmt.vbi;

	vbifmt->sampling_rate = 27000000;
	vbifmt->offset = 248; /* FIXME - slightly wrong for both 50 & 60 Hz */
	vbifmt->samples_per_line = vbi_active_samples - 4;
	vbifmt->sample_format = V4L2_PIX_FMT_GREY;
	vbifmt->start[0] = cx->vbi.start[0];
	vbifmt->start[1] = cx->vbi.start[1];
	vbifmt->count[0] = vbifmt->count[1] = cx->vbi.count;
	vbifmt->flags = 0;
	vbifmt->reserved[0] = 0;
	vbifmt->reserved[1] = 0;
	return 0;
}