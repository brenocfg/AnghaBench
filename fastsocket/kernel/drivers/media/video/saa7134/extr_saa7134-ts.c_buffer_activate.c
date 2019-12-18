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
struct TYPE_3__ {int /*<<< orphan*/  timeout; } ;
struct saa7134_dev {int /*<<< orphan*/  ts_started; TYPE_1__ ts_q; } ;
struct TYPE_4__ {scalar_t__ field; int /*<<< orphan*/  state; } ;
struct saa7134_buf {TYPE_2__ vb; scalar_t__ top_seen; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAA7134_RS_BA1 (int) ; 
 int /*<<< orphan*/  SAA7134_RS_BA2 (int) ; 
 scalar_t__ TS_BUFFER_TIMEOUT ; 
 scalar_t__ V4L2_FIELD_TOP ; 
 int /*<<< orphan*/  VIDEOBUF_ACTIVE ; 
 int /*<<< orphan*/  dprintk (char*,struct saa7134_buf*,...) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  saa7134_buffer_base (struct saa7134_buf*) ; 
 int /*<<< orphan*/  saa7134_set_dmabits (struct saa7134_dev*) ; 
 int /*<<< orphan*/  saa7134_ts_start (struct saa7134_dev*) ; 
 int /*<<< orphan*/  saa_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int buffer_activate(struct saa7134_dev *dev,
			   struct saa7134_buf *buf,
			   struct saa7134_buf *next)
{

	dprintk("buffer_activate [%p]",buf);
	buf->vb.state = VIDEOBUF_ACTIVE;
	buf->top_seen = 0;

	if (NULL == next)
		next = buf;
	if (V4L2_FIELD_TOP == buf->vb.field) {
		dprintk("- [top]     buf=%p next=%p\n",buf,next);
		saa_writel(SAA7134_RS_BA1(5),saa7134_buffer_base(buf));
		saa_writel(SAA7134_RS_BA2(5),saa7134_buffer_base(next));
	} else {
		dprintk("- [bottom]  buf=%p next=%p\n",buf,next);
		saa_writel(SAA7134_RS_BA1(5),saa7134_buffer_base(next));
		saa_writel(SAA7134_RS_BA2(5),saa7134_buffer_base(buf));
	}

	/* start DMA */
	saa7134_set_dmabits(dev);

	mod_timer(&dev->ts_q.timeout, jiffies+TS_BUFFER_TIMEOUT);

	if (!dev->ts_started)
		saa7134_ts_start(dev);

	return 0;
}