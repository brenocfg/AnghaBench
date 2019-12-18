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
struct vivi_fh {int /*<<< orphan*/  vb_vidq; struct vivi_dev* dev; } ;
struct vivi_dmaqueue {int dummy; } ;
struct vivi_dev {int /*<<< orphan*/  users; int /*<<< orphan*/  mutex; struct vivi_dmaqueue vidq; } ;
struct file {struct vivi_fh* private_data; } ;
struct TYPE_2__ {int minor; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (struct vivi_dev*,int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct vivi_fh*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* video_devdata (struct file*) ; 
 int /*<<< orphan*/  videobuf_mmap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  videobuf_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vivi_stop_thread (struct vivi_dmaqueue*) ; 

__attribute__((used)) static int vivi_close(struct file *file)
{
	struct vivi_fh         *fh = file->private_data;
	struct vivi_dev *dev       = fh->dev;
	struct vivi_dmaqueue *vidq = &dev->vidq;

	int minor = video_devdata(file)->minor;

	vivi_stop_thread(vidq);
	videobuf_stop(&fh->vb_vidq);
	videobuf_mmap_free(&fh->vb_vidq);

	kfree(fh);

	mutex_lock(&dev->mutex);
	dev->users--;
	mutex_unlock(&dev->mutex);

	dprintk(dev, 1, "close called (minor=%d, users=%d)\n",
		minor, dev->users);

	return 0;
}