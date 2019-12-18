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
struct file {struct cx8802_fh* private_data; } ;
struct cx8802_fh {int /*<<< orphan*/  mpegq; struct cx8802_dev* dev; } ;
struct cx8802_driver {int /*<<< orphan*/  (* request_release ) (struct cx8802_driver*) ;} ;
struct cx8802_dev {TYPE_1__* core; scalar_t__ mpeg_active; } ;
struct TYPE_2__ {int /*<<< orphan*/  mpeg_users; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX88_MPEG_BLACKBIRD ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blackbird_stop_codec (struct cx8802_dev*) ; 
 int /*<<< orphan*/  cx8802_cancel_buffers (struct cx8802_dev*) ; 
 struct cx8802_driver* cx8802_get_driver (struct cx8802_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cx8802_fh*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct cx8802_driver*) ; 
 int /*<<< orphan*/  videobuf_mmap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  videobuf_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mpeg_release(struct file *file)
{
	struct cx8802_fh  *fh  = file->private_data;
	struct cx8802_dev *dev = fh->dev;
	struct cx8802_driver *drv = NULL;

	if (dev->mpeg_active && atomic_read(&dev->core->mpeg_users) == 1)
		blackbird_stop_codec(dev);

	cx8802_cancel_buffers(fh->dev);
	/* stop mpeg capture */
	videobuf_stop(&fh->mpegq);

	videobuf_mmap_free(&fh->mpegq);

	mutex_lock(&dev->core->lock);
	file->private_data = NULL;
	kfree(fh);
	mutex_unlock(&dev->core->lock);

	/* Make sure we release the hardware */
	drv = cx8802_get_driver(dev, CX88_MPEG_BLACKBIRD);
	if (drv)
		drv->request_release(drv);

	atomic_dec(&dev->core->mpeg_users);

	return 0;
}