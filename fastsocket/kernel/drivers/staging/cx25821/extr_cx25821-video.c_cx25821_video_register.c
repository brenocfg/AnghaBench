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
struct video_device {int /*<<< orphan*/  current_norm; } ;
struct cx25821_dev {size_t nr; int /*<<< orphan*/  lock; int /*<<< orphan*/  tvnorm; int /*<<< orphan*/ * video_dev; int /*<<< orphan*/  pci; TYPE_3__* sram_channels; TYPE_2__* vidq; TYPE_1__* timeout_data; int /*<<< orphan*/  slock; } ;
struct TYPE_8__ {unsigned long data; int /*<<< orphan*/  function; } ;
struct TYPE_7__ {int /*<<< orphan*/  dma_ctl; } ;
struct TYPE_6__ {int /*<<< orphan*/  stopper; TYPE_4__ timeout; int /*<<< orphan*/  queued; int /*<<< orphan*/  active; } ;
struct TYPE_5__ {TYPE_3__* channel; struct cx25821_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PCI_INT_MSK ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  cx25821_risc_stopper (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx25821_set_tvnorm (struct cx25821_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx25821_vdev_init (struct cx25821_dev*,int /*<<< orphan*/ ,struct video_device*,char*) ; 
 int /*<<< orphan*/  cx25821_vid_timeout ; 
 int /*<<< orphan*/  cx25821_video_unregister (struct cx25821_dev*,int) ; 
 int /*<<< orphan*/  cx_set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  init_controls (struct cx25821_dev*,int) ; 
 int /*<<< orphan*/  init_timer (TYPE_4__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * video_nr ; 
 int video_register_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cx25821_video_register(struct cx25821_dev *dev, int chan_num,
			   struct video_device *video_template)
{
	int err;

	spin_lock_init(&dev->slock);

	//printk(KERN_WARNING "Channel %d\n", chan_num);

#ifdef TUNER_FLAG
	dev->tvnorm = video_template->current_norm;
#endif

	/* init video dma queues */
	dev->timeout_data[chan_num].dev = dev;
	dev->timeout_data[chan_num].channel = &dev->sram_channels[chan_num];
	INIT_LIST_HEAD(&dev->vidq[chan_num].active);
	INIT_LIST_HEAD(&dev->vidq[chan_num].queued);
	dev->vidq[chan_num].timeout.function = cx25821_vid_timeout;
	dev->vidq[chan_num].timeout.data =
	    (unsigned long)&dev->timeout_data[chan_num];
	init_timer(&dev->vidq[chan_num].timeout);
	cx25821_risc_stopper(dev->pci, &dev->vidq[chan_num].stopper,
			     dev->sram_channels[chan_num].dma_ctl, 0x11, 0);

	/* register v4l devices */
	dev->video_dev[chan_num] =
	    cx25821_vdev_init(dev, dev->pci, video_template, "video");
	err =
	    video_register_device(dev->video_dev[chan_num], VFL_TYPE_GRABBER,
				  video_nr[dev->nr]);

	if (err < 0) {
		goto fail_unreg;
	}
	//set PCI interrupt
	cx_set(PCI_INT_MSK, 0xff);

	/* initial device configuration */
	mutex_lock(&dev->lock);
#ifdef TUNER_FLAG
	cx25821_set_tvnorm(dev, dev->tvnorm);
#endif
	mutex_unlock(&dev->lock);

	init_controls(dev, chan_num);

	return 0;

      fail_unreg:
	cx25821_video_unregister(dev, chan_num);
	return err;
}