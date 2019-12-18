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
struct stk_camera {int n_sbufs; int /*<<< orphan*/  spinlock; TYPE_2__* sio_bufs; int /*<<< orphan*/  sio_full; int /*<<< orphan*/  sio_avail; } ;
struct file {int dummy; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;
struct TYPE_3__ {scalar_t__ flags; } ;
struct TYPE_4__ {TYPE_1__ v4lbuf; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stk_stop_stream (struct stk_camera*) ; 

__attribute__((used)) static int stk_vidioc_streamoff(struct file *filp,
		void *priv, enum v4l2_buf_type type)
{
	struct stk_camera *dev = priv;
	unsigned long flags;
	int i;
	stk_stop_stream(dev);
	spin_lock_irqsave(&dev->spinlock, flags);
	INIT_LIST_HEAD(&dev->sio_avail);
	INIT_LIST_HEAD(&dev->sio_full);
	for (i = 0; i < dev->n_sbufs; i++) {
		INIT_LIST_HEAD(&dev->sio_bufs[i].list);
		dev->sio_bufs[i].v4lbuf.flags = 0;
	}
	spin_unlock_irqrestore(&dev->spinlock, flags);
	return 0;
}