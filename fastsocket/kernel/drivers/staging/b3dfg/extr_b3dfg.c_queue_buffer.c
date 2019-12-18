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
struct device {int dummy; } ;
struct b3dfg_dev {int /*<<< orphan*/  buffer_lock; scalar_t__ triplet_ready; scalar_t__ transmission_enabled; int /*<<< orphan*/  buffer_queue; struct b3dfg_buffer* buffers; TYPE_1__* pdev; } ;
struct b3dfg_buffer {scalar_t__ state; int /*<<< orphan*/  list; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 scalar_t__ B3DFG_BUFFER_PENDING ; 
 int EINVAL ; 
 int ENOENT ; 
 int b3dfg_nbuf ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int setup_frame_transfer (struct b3dfg_dev*,struct b3dfg_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int queue_buffer(struct b3dfg_dev *fgdev, int bufidx)
{
	struct device *dev = &fgdev->pdev->dev;
	struct b3dfg_buffer *buf;
	unsigned long flags;
	int r = 0;

	spin_lock_irqsave(&fgdev->buffer_lock, flags);
	if (bufidx < 0 || bufidx >= b3dfg_nbuf) {
		dev_dbg(dev, "Invalid buffer index, %d\n", bufidx);
		r = -ENOENT;
		goto out;
	}
	buf = &fgdev->buffers[bufidx];

	if (unlikely(buf->state == B3DFG_BUFFER_PENDING)) {
		dev_dbg(dev, "buffer %d is already queued\n", bufidx);
		r = -EINVAL;
		goto out;
	}

	buf->state = B3DFG_BUFFER_PENDING;
	list_add_tail(&buf->list, &fgdev->buffer_queue);

	if (fgdev->transmission_enabled && fgdev->triplet_ready) {
		dev_dbg(dev, "triplet is ready, pushing immediately\n");
		fgdev->triplet_ready = 0;
		r = setup_frame_transfer(fgdev, buf, 0);
		if (r)
			dev_err(dev, "unable to map DMA buffer\n");
	}

out:
	spin_unlock_irqrestore(&fgdev->buffer_lock, flags);
	return r;
}