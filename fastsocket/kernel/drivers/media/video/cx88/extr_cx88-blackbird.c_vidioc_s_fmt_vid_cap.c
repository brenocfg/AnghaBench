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
struct TYPE_5__ {int sizeimage; int /*<<< orphan*/  field; int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ colorspace; scalar_t__ bytesperline; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_6__ {TYPE_2__ pix; } ;
struct v4l2_format {TYPE_3__ fmt; } ;
struct file {int dummy; } ;
struct cx88_core {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  field; } ;
struct cx8802_fh {TYPE_1__ mpegq; struct cx8802_dev* dev; } ;
struct cx8802_dev {int ts_packet_size; int ts_packet_count; int /*<<< orphan*/  height; int /*<<< orphan*/  width; struct cx88_core* core; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX2341X_ENC_SET_FRAME_SIZE ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_MPEG ; 
 int /*<<< orphan*/  blackbird_api_cmd (struct cx8802_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx88_set_scale (struct cx88_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vidioc_s_fmt_vid_cap (struct file *file, void *priv,
					struct v4l2_format *f)
{
	struct cx8802_fh  *fh   = priv;
	struct cx8802_dev *dev  = fh->dev;
	struct cx88_core  *core = dev->core;

	f->fmt.pix.pixelformat  = V4L2_PIX_FMT_MPEG;
	f->fmt.pix.bytesperline = 0;
	f->fmt.pix.sizeimage    = dev->ts_packet_size * dev->ts_packet_count; /* 188 * 4 * 1024; */;
	f->fmt.pix.colorspace   = 0;
	dev->width              = f->fmt.pix.width;
	dev->height             = f->fmt.pix.height;
	fh->mpegq.field         = f->fmt.pix.field;
	cx88_set_scale(core, f->fmt.pix.width, f->fmt.pix.height, f->fmt.pix.field);
	blackbird_api_cmd(dev, CX2341X_ENC_SET_FRAME_SIZE, 2, 0,
				f->fmt.pix.height, f->fmt.pix.width);
	dprintk(0,"VIDIOC_S_FMT: w: %d, h: %d, f: %d\n",
		f->fmt.pix.width, f->fmt.pix.height, f->fmt.pix.field );
	return 0;
}