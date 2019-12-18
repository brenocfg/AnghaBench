#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct saa7134_dmaqueue {scalar_t__ curr; struct saa7134_dev* dev; } ;
struct saa7134_dev {int /*<<< orphan*/  slock; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAA7134_REGION_ENABLE ; 
 int /*<<< orphan*/  VIDEOBUF_ERROR ; 
 int /*<<< orphan*/  dprintk (char*,scalar_t__) ; 
 int /*<<< orphan*/  saa7134_buffer_finish (struct saa7134_dev*,struct saa7134_dmaqueue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa7134_buffer_next (struct saa7134_dev*,struct saa7134_dmaqueue*) ; 
 int /*<<< orphan*/  saa_writeb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void saa7134_buffer_timeout(unsigned long data)
{
	struct saa7134_dmaqueue *q = (struct saa7134_dmaqueue*)data;
	struct saa7134_dev *dev = q->dev;
	unsigned long flags;

	spin_lock_irqsave(&dev->slock,flags);

	/* try to reset the hardware (SWRST) */
	saa_writeb(SAA7134_REGION_ENABLE, 0x00);
	saa_writeb(SAA7134_REGION_ENABLE, 0x80);
	saa_writeb(SAA7134_REGION_ENABLE, 0x00);

	/* flag current buffer as failed,
	   try to start over with the next one. */
	if (q->curr) {
		dprintk("timeout on %p\n",q->curr);
		saa7134_buffer_finish(dev,q,VIDEOBUF_ERROR);
	}
	saa7134_buffer_next(dev,q);
	spin_unlock_irqrestore(&dev->slock,flags);
}