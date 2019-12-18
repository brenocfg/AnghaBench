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
struct TYPE_3__ {int samples_per_line; int sampling_rate; int* start; int* count; scalar_t__ flags; scalar_t__ offset; int /*<<< orphan*/  sample_format; } ;
struct TYPE_4__ {TYPE_1__ vbi; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_PIX_FMT_GREY ; 

int saa7164_vbi_fmt(struct file *file, void *priv, struct v4l2_format *f)
{
	/* ntsc */
	f->fmt.vbi.samples_per_line = 1600;
	f->fmt.vbi.samples_per_line = 1440;
	f->fmt.vbi.sampling_rate = 27000000;
	f->fmt.vbi.sample_format = V4L2_PIX_FMT_GREY;
	f->fmt.vbi.offset = 0;
	f->fmt.vbi.flags = 0;
	f->fmt.vbi.start[0] = 10;
	f->fmt.vbi.count[0] = 18;
	f->fmt.vbi.start[1] = 263 + 10 + 1;
	f->fmt.vbi.count[1] = 18;
	return 0;
}