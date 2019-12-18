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
struct TYPE_6__ {int /*<<< orphan*/  timeout; } ;
struct saa7134_dev {TYPE_3__ vbi_q; } ;
struct TYPE_5__ {int size; unsigned long width; int /*<<< orphan*/  state; } ;
struct saa7134_buf {TYPE_2__ vb; TYPE_1__* pt; scalar_t__ top_seen; } ;
struct TYPE_4__ {int dma; } ;

/* Variables and functions */
 scalar_t__ BUFFER_TIMEOUT ; 
 int /*<<< orphan*/  SAA7134_OFMT_DATA_A ; 
 int /*<<< orphan*/  SAA7134_OFMT_DATA_B ; 
 int /*<<< orphan*/  SAA7134_RS_BA1 (int) ; 
 int /*<<< orphan*/  SAA7134_RS_BA2 (int) ; 
 int /*<<< orphan*/  SAA7134_RS_CONTROL (int) ; 
 int SAA7134_RS_CONTROL_BURST_16 ; 
 int SAA7134_RS_CONTROL_ME ; 
 int /*<<< orphan*/  SAA7134_RS_PITCH (int) ; 
 int /*<<< orphan*/  TASK_A ; 
 int /*<<< orphan*/  TASK_B ; 
 int /*<<< orphan*/  VIDEOBUF_ACTIVE ; 
 int /*<<< orphan*/  dprintk (char*,struct saa7134_buf*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 unsigned long saa7134_buffer_base (struct saa7134_buf*) ; 
 int /*<<< orphan*/  saa7134_set_dmabits (struct saa7134_dev*) ; 
 int /*<<< orphan*/  saa_writeb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  saa_writel (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  task_init (struct saa7134_dev*,struct saa7134_buf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int buffer_activate(struct saa7134_dev *dev,
			   struct saa7134_buf *buf,
			   struct saa7134_buf *next)
{
	unsigned long control,base;

	dprintk("buffer_activate [%p]\n",buf);
	buf->vb.state = VIDEOBUF_ACTIVE;
	buf->top_seen = 0;

	task_init(dev,buf,TASK_A);
	task_init(dev,buf,TASK_B);
	saa_writeb(SAA7134_OFMT_DATA_A, 0x06);
	saa_writeb(SAA7134_OFMT_DATA_B, 0x06);

	/* DMA: setup channel 2+3 (= VBI Task A+B) */
	base    = saa7134_buffer_base(buf);
	control = SAA7134_RS_CONTROL_BURST_16 |
		SAA7134_RS_CONTROL_ME |
		(buf->pt->dma >> 12);
	saa_writel(SAA7134_RS_BA1(2),base);
	saa_writel(SAA7134_RS_BA2(2),base + buf->vb.size/2);
	saa_writel(SAA7134_RS_PITCH(2),buf->vb.width);
	saa_writel(SAA7134_RS_CONTROL(2),control);
	saa_writel(SAA7134_RS_BA1(3),base);
	saa_writel(SAA7134_RS_BA2(3),base + buf->vb.size/2);
	saa_writel(SAA7134_RS_PITCH(3),buf->vb.width);
	saa_writel(SAA7134_RS_CONTROL(3),control);

	/* start DMA */
	saa7134_set_dmabits(dev);
	mod_timer(&dev->vbi_q.timeout, jiffies+BUFFER_TIMEOUT);

	return 0;
}