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
struct TYPE_2__ {int /*<<< orphan*/  timeout; scalar_t__ curr; } ;
struct saa7146_vv {TYPE_1__ vbi_q; int /*<<< orphan*/ * vbi_streaming; } ;
struct saa7146_fh {int /*<<< orphan*/  vbi_read_timeout; int /*<<< orphan*/  vbi_q; struct saa7146_dev* dev; } ;
struct saa7146_dev {int /*<<< orphan*/  slock; struct saa7146_vv* vv_data; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB_VBI (char*) ; 
 int /*<<< orphan*/  MASK_20 ; 
 int /*<<< orphan*/  MASK_28 ; 
 int /*<<< orphan*/  MASK_29 ; 
 int /*<<< orphan*/  MC1 ; 
 int /*<<< orphan*/  SAA7146_IER_DISABLE (struct saa7146_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIDEOBUF_DONE ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  saa7146_buffer_finish (struct saa7146_dev*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa7146_write (struct saa7146_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  videobuf_queue_cancel (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vbi_stop(struct saa7146_fh *fh, struct file *file)
{
	struct saa7146_dev *dev = fh->dev;
	struct saa7146_vv *vv = dev->vv_data;
	unsigned long flags;
	DEB_VBI(("dev:%p, fh:%p\n",dev, fh));

	spin_lock_irqsave(&dev->slock,flags);

	/* disable rps1  */
	saa7146_write(dev, MC1, MASK_29);

	/* disable rps1 irqs */
	SAA7146_IER_DISABLE(dev, MASK_28);

	/* shut down dma 3 transfers */
	saa7146_write(dev, MC1, MASK_20);

	if (vv->vbi_q.curr) {
		saa7146_buffer_finish(dev,&vv->vbi_q,VIDEOBUF_DONE);
	}

	videobuf_queue_cancel(&fh->vbi_q);

	vv->vbi_streaming = NULL;

	del_timer(&vv->vbi_q.timeout);
	del_timer(&fh->vbi_read_timeout);

	spin_unlock_irqrestore(&dev->slock, flags);
}