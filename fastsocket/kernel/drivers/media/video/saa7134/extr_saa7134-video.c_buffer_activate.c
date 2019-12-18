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
struct TYPE_8__ {int /*<<< orphan*/  timeout; } ;
struct saa7134_dev {TYPE_4__ video_q; } ;
struct TYPE_7__ {unsigned long width; unsigned long height; int /*<<< orphan*/  field; int /*<<< orphan*/  state; } ;
struct saa7134_buf {TYPE_3__ vb; TYPE_2__* fmt; TYPE_1__* pt; scalar_t__ top_seen; } ;
struct TYPE_6__ {int depth; unsigned long hshift; unsigned long vshift; scalar_t__ uvswap; scalar_t__ planar; scalar_t__ wswap; scalar_t__ bswap; int /*<<< orphan*/  pm; scalar_t__ yuv; } ;
struct TYPE_5__ {int dma; } ;

/* Variables and functions */
 scalar_t__ BUFFER_TIMEOUT ; 
 int /*<<< orphan*/  SAA7134_DATA_PATH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAA7134_OFMT_VIDEO_A ; 
 int /*<<< orphan*/  SAA7134_RS_BA1 (int) ; 
 int /*<<< orphan*/  SAA7134_RS_BA2 (int) ; 
 int /*<<< orphan*/  SAA7134_RS_CONTROL (int) ; 
 unsigned long SAA7134_RS_CONTROL_BSWAP ; 
 int SAA7134_RS_CONTROL_BURST_16 ; 
 int SAA7134_RS_CONTROL_ME ; 
 unsigned long SAA7134_RS_CONTROL_WSWAP ; 
 int /*<<< orphan*/  SAA7134_RS_PITCH (int) ; 
 int /*<<< orphan*/  TASK_A ; 
 scalar_t__ V4L2_FIELD_HAS_BOTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIDEOBUF_ACTIVE ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 unsigned long saa7134_buffer_base (struct saa7134_buf*) ; 
 int /*<<< orphan*/  saa7134_set_dmabits (struct saa7134_dev*) ; 
 int /*<<< orphan*/  saa_andorb (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  saa_writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa_writel (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  set_size (struct saa7134_dev*,int /*<<< orphan*/ ,unsigned long,unsigned long,scalar_t__) ; 

__attribute__((used)) static int buffer_activate(struct saa7134_dev *dev,
			   struct saa7134_buf *buf,
			   struct saa7134_buf *next)
{
	unsigned long base,control,bpl;
	unsigned long bpl_uv,lines_uv,base2,base3,tmp; /* planar */

	dprintk("buffer_activate buf=%p\n",buf);
	buf->vb.state = VIDEOBUF_ACTIVE;
	buf->top_seen = 0;

	set_size(dev,TASK_A,buf->vb.width,buf->vb.height,
		 V4L2_FIELD_HAS_BOTH(buf->vb.field));
	if (buf->fmt->yuv)
		saa_andorb(SAA7134_DATA_PATH(TASK_A), 0x3f, 0x03);
	else
		saa_andorb(SAA7134_DATA_PATH(TASK_A), 0x3f, 0x01);
	saa_writeb(SAA7134_OFMT_VIDEO_A, buf->fmt->pm);

	/* DMA: setup channel 0 (= Video Task A0) */
	base  = saa7134_buffer_base(buf);
	if (buf->fmt->planar)
		bpl = buf->vb.width;
	else
		bpl = (buf->vb.width * buf->fmt->depth) / 8;
	control = SAA7134_RS_CONTROL_BURST_16 |
		SAA7134_RS_CONTROL_ME |
		(buf->pt->dma >> 12);
	if (buf->fmt->bswap)
		control |= SAA7134_RS_CONTROL_BSWAP;
	if (buf->fmt->wswap)
		control |= SAA7134_RS_CONTROL_WSWAP;
	if (V4L2_FIELD_HAS_BOTH(buf->vb.field)) {
		/* interlaced */
		saa_writel(SAA7134_RS_BA1(0),base);
		saa_writel(SAA7134_RS_BA2(0),base+bpl);
		saa_writel(SAA7134_RS_PITCH(0),bpl*2);
	} else {
		/* non-interlaced */
		saa_writel(SAA7134_RS_BA1(0),base);
		saa_writel(SAA7134_RS_BA2(0),base);
		saa_writel(SAA7134_RS_PITCH(0),bpl);
	}
	saa_writel(SAA7134_RS_CONTROL(0),control);

	if (buf->fmt->planar) {
		/* DMA: setup channel 4+5 (= planar task A) */
		bpl_uv   = bpl >> buf->fmt->hshift;
		lines_uv = buf->vb.height >> buf->fmt->vshift;
		base2    = base + bpl * buf->vb.height;
		base3    = base2 + bpl_uv * lines_uv;
		if (buf->fmt->uvswap)
			tmp = base2, base2 = base3, base3 = tmp;
		dprintk("uv: bpl=%ld lines=%ld base2/3=%ld/%ld\n",
			bpl_uv,lines_uv,base2,base3);
		if (V4L2_FIELD_HAS_BOTH(buf->vb.field)) {
			/* interlaced */
			saa_writel(SAA7134_RS_BA1(4),base2);
			saa_writel(SAA7134_RS_BA2(4),base2+bpl_uv);
			saa_writel(SAA7134_RS_PITCH(4),bpl_uv*2);
			saa_writel(SAA7134_RS_BA1(5),base3);
			saa_writel(SAA7134_RS_BA2(5),base3+bpl_uv);
			saa_writel(SAA7134_RS_PITCH(5),bpl_uv*2);
		} else {
			/* non-interlaced */
			saa_writel(SAA7134_RS_BA1(4),base2);
			saa_writel(SAA7134_RS_BA2(4),base2);
			saa_writel(SAA7134_RS_PITCH(4),bpl_uv);
			saa_writel(SAA7134_RS_BA1(5),base3);
			saa_writel(SAA7134_RS_BA2(5),base3);
			saa_writel(SAA7134_RS_PITCH(5),bpl_uv);
		}
		saa_writel(SAA7134_RS_CONTROL(4),control);
		saa_writel(SAA7134_RS_CONTROL(5),control);
	}

	/* start DMA */
	saa7134_set_dmabits(dev);
	mod_timer(&dev->video_q.timeout, jiffies+BUFFER_TIMEOUT);
	return 0;
}