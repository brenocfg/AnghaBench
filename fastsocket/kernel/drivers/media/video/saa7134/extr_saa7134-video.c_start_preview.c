#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int left; unsigned long top; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_10__ {size_t field; TYPE_1__ w; } ;
struct saa7134_fh {TYPE_5__ win; int /*<<< orphan*/  nclips; int /*<<< orphan*/  clips; } ;
struct TYPE_7__ {unsigned long bytesperline; } ;
struct TYPE_8__ {TYPE_2__ fmt; scalar_t__ base; } ;
struct saa7134_dev {size_t ovfield; int ovenable; TYPE_4__* ovfmt; TYPE_3__ ovbuf; } ;
struct TYPE_9__ {int pm; int depth; scalar_t__ wswap; scalar_t__ bswap; scalar_t__ yuv; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAA7134_DATA_PATH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAA7134_OFMT_VIDEO_B ; 
 int /*<<< orphan*/  SAA7134_RS_BA1 (int) ; 
 int /*<<< orphan*/  SAA7134_RS_BA2 (int) ; 
 int /*<<< orphan*/  SAA7134_RS_CONTROL (int) ; 
 unsigned long SAA7134_RS_CONTROL_BSWAP ; 
 unsigned long SAA7134_RS_CONTROL_BURST_16 ; 
 unsigned long SAA7134_RS_CONTROL_WSWAP ; 
 int /*<<< orphan*/  SAA7134_RS_PITCH (int) ; 
 int /*<<< orphan*/  TASK_B ; 
 scalar_t__ V4L2_FIELD_HAS_BOTH (size_t) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa7134_set_dmabits (struct saa7134_dev*) ; 
 int /*<<< orphan*/  saa_andorb (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  saa_writeb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  saa_writel (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  set_size (struct saa7134_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  setup_clipping (struct saa7134_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * v4l2_field_names ; 
 int verify_preview (struct saa7134_dev*,TYPE_5__*) ; 

__attribute__((used)) static int start_preview(struct saa7134_dev *dev, struct saa7134_fh *fh)
{
	unsigned long base,control,bpl;
	int err;

	err = verify_preview(dev,&fh->win);
	if (0 != err)
		return err;

	dev->ovfield = fh->win.field;
	dprintk("start_preview %dx%d+%d+%d %s field=%s\n",
		fh->win.w.width,fh->win.w.height,
		fh->win.w.left,fh->win.w.top,
		dev->ovfmt->name,v4l2_field_names[dev->ovfield]);

	/* setup window + clipping */
	set_size(dev,TASK_B,fh->win.w.width,fh->win.w.height,
		 V4L2_FIELD_HAS_BOTH(dev->ovfield));
	setup_clipping(dev,fh->clips,fh->nclips,
		       V4L2_FIELD_HAS_BOTH(dev->ovfield));
	if (dev->ovfmt->yuv)
		saa_andorb(SAA7134_DATA_PATH(TASK_B), 0x3f, 0x03);
	else
		saa_andorb(SAA7134_DATA_PATH(TASK_B), 0x3f, 0x01);
	saa_writeb(SAA7134_OFMT_VIDEO_B, dev->ovfmt->pm | 0x20);

	/* dma: setup channel 1 (= Video Task B) */
	base  = (unsigned long)dev->ovbuf.base;
	base += dev->ovbuf.fmt.bytesperline * fh->win.w.top;
	base += dev->ovfmt->depth/8         * fh->win.w.left;
	bpl   = dev->ovbuf.fmt.bytesperline;
	control = SAA7134_RS_CONTROL_BURST_16;
	if (dev->ovfmt->bswap)
		control |= SAA7134_RS_CONTROL_BSWAP;
	if (dev->ovfmt->wswap)
		control |= SAA7134_RS_CONTROL_WSWAP;
	if (V4L2_FIELD_HAS_BOTH(dev->ovfield)) {
		saa_writel(SAA7134_RS_BA1(1),base);
		saa_writel(SAA7134_RS_BA2(1),base+bpl);
		saa_writel(SAA7134_RS_PITCH(1),bpl*2);
		saa_writel(SAA7134_RS_CONTROL(1),control);
	} else {
		saa_writel(SAA7134_RS_BA1(1),base);
		saa_writel(SAA7134_RS_BA2(1),base);
		saa_writel(SAA7134_RS_PITCH(1),bpl);
		saa_writel(SAA7134_RS_CONTROL(1),control);
	}

	/* start dma */
	dev->ovenable = 1;
	saa7134_set_dmabits(dev);

	return 0;
}