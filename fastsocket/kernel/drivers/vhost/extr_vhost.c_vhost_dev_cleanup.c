#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vhost_dev {int nvqs; int /*<<< orphan*/ * mm; int /*<<< orphan*/ * worker; int /*<<< orphan*/  work_list; int /*<<< orphan*/ * memory; int /*<<< orphan*/ * log_file; int /*<<< orphan*/ * log_ctx; TYPE_1__* vqs; } ;
struct TYPE_3__ {int /*<<< orphan*/ * call; int /*<<< orphan*/ * call_ctx; int /*<<< orphan*/ * kick; int /*<<< orphan*/ * error; int /*<<< orphan*/ * error_ctx; scalar_t__ ubufs; int /*<<< orphan*/  poll; scalar_t__ handle_kick; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  eventfd_ctx_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fput (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmput (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vhost_dev_free_iovecs (struct vhost_dev*) ; 
 int /*<<< orphan*/  vhost_poll_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vhost_poll_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vhost_ubuf_put_and_wait (scalar_t__) ; 
 int /*<<< orphan*/  vhost_vq_reset (struct vhost_dev*,TYPE_1__*) ; 
 int /*<<< orphan*/  vhost_zerocopy_signal_used (TYPE_1__*) ; 

void vhost_dev_cleanup(struct vhost_dev *dev)
{
	int i;
	for (i = 0; i < dev->nvqs; ++i) {
		if (dev->vqs[i].kick && dev->vqs[i].handle_kick) {
			vhost_poll_stop(&dev->vqs[i].poll);
			vhost_poll_flush(&dev->vqs[i].poll);
		}
		/* Wait for all lower device DMAs done. */
		if (dev->vqs[i].ubufs)
			vhost_ubuf_put_and_wait(dev->vqs[i].ubufs);

		/* Signal guest as appropriate. */
		vhost_zerocopy_signal_used(&dev->vqs[i]);

		if (dev->vqs[i].error_ctx)
			eventfd_ctx_put(dev->vqs[i].error_ctx);
		if (dev->vqs[i].error)
			fput(dev->vqs[i].error);
		if (dev->vqs[i].kick)
			fput(dev->vqs[i].kick);
		if (dev->vqs[i].call_ctx)
			eventfd_ctx_put(dev->vqs[i].call_ctx);
		if (dev->vqs[i].call)
			fput(dev->vqs[i].call);
		vhost_vq_reset(dev, dev->vqs + i);
	}
	vhost_dev_free_iovecs(dev);
	if (dev->log_ctx)
		eventfd_ctx_put(dev->log_ctx);
	dev->log_ctx = NULL;
	if (dev->log_file)
		fput(dev->log_file);
	dev->log_file = NULL;
	/* No one will access memory at this point */
	kfree(dev->memory);
	dev->memory = NULL;
	WARN_ON(!list_empty(&dev->work_list));
	if (dev->worker) {
		kthread_stop(dev->worker);
		dev->worker = NULL;
	}
	if (dev->mm)
		mmput(dev->mm);
	dev->mm = NULL;
}