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
struct vhost_virtqueue {scalar_t__ handle_kick; int /*<<< orphan*/  poll; int /*<<< orphan*/  mutex; struct vhost_dev* dev; int /*<<< orphan*/ * ubuf_info; int /*<<< orphan*/ * heads; int /*<<< orphan*/ * indirect; int /*<<< orphan*/ * log; } ;
struct vhost_dev {int nvqs; struct vhost_virtqueue* vqs; int /*<<< orphan*/ * worker; int /*<<< orphan*/  work_list; int /*<<< orphan*/  work_lock; int /*<<< orphan*/ * mm; int /*<<< orphan*/ * memory; int /*<<< orphan*/ * log_file; int /*<<< orphan*/ * log_ctx; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  POLLIN ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vhost_poll_init (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,struct vhost_dev*) ; 
 int /*<<< orphan*/  vhost_vq_reset (struct vhost_dev*,struct vhost_virtqueue*) ; 

long vhost_dev_init(struct vhost_dev *dev,
		    struct vhost_virtqueue *vqs, int nvqs)
{
	int i;

	dev->vqs = vqs;
	dev->nvqs = nvqs;
	mutex_init(&dev->mutex);
	dev->log_ctx = NULL;
	dev->log_file = NULL;
	dev->memory = NULL;
	dev->mm = NULL;
	spin_lock_init(&dev->work_lock);
	INIT_LIST_HEAD(&dev->work_list);
	dev->worker = NULL;

	for (i = 0; i < dev->nvqs; ++i) {
		dev->vqs[i].log = NULL;
		dev->vqs[i].indirect = NULL;
		dev->vqs[i].heads = NULL;
		dev->vqs[i].ubuf_info = NULL;
		dev->vqs[i].dev = dev;
		mutex_init(&dev->vqs[i].mutex);
		vhost_vq_reset(dev, dev->vqs + i);
		if (dev->vqs[i].handle_kick)
			vhost_poll_init(&dev->vqs[i].poll,
					dev->vqs[i].handle_kick, POLLIN, dev);
	}

	return 0;
}