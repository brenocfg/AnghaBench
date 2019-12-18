#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int sizeimage; scalar_t__ colorspace; scalar_t__ bytesperline; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_6__ {TYPE_1__ pix; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct file {struct cx231xx_fh* private_data; } ;
struct TYPE_8__ {int /*<<< orphan*/  field; } ;
struct cx231xx_fh {TYPE_4__ vidq; struct cx231xx* dev; } ;
struct TYPE_7__ {int ts_packet_size; int ts_packet_count; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct cx231xx {TYPE_3__ ts1; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_PIX_FMT_MPEG ; 
 int /*<<< orphan*/  dprintk (int,char*,...) ; 

__attribute__((used)) static int vidioc_try_fmt_vid_cap(struct file *file, void *priv,
				struct v4l2_format *f)
{
	struct cx231xx_fh  *fh  = file->private_data;
	struct cx231xx *dev = fh->dev;
	dprintk(3, "enter vidioc_try_fmt_vid_cap()\n");
	f->fmt.pix.pixelformat  = V4L2_PIX_FMT_MPEG;
	f->fmt.pix.bytesperline = 0;
	f->fmt.pix.sizeimage    =
		dev->ts1.ts_packet_size * dev->ts1.ts_packet_count;
	f->fmt.pix.colorspace   = 0;
	dprintk(1, "VIDIOC_TRY_FMT: w: %d, h: %d, f: %d\n",
		dev->ts1.width, dev->ts1.height, fh->vidq.field);
	dprintk(3, "exit vidioc_try_fmt_vid_cap()\n");
	return 0;
}