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
struct stk_camera {int n_sbufs; TYPE_1__* sio_bufs; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  sio_full; int /*<<< orphan*/  sio_avail; } ;
struct TYPE_2__ {scalar_t__ mapcount; int /*<<< orphan*/ * buffer; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stk_free_sio_buffers(struct stk_camera *dev)
{
	int i;
	int nbufs;
	unsigned long flags;
	if (dev->n_sbufs == 0 || dev->sio_bufs == NULL)
		return 0;
	/*
	* If any buffers are mapped, we cannot free them at all.
	*/
	for (i = 0; i < dev->n_sbufs; i++) {
		if (dev->sio_bufs[i].mapcount > 0)
			return -EBUSY;
	}
	/*
	* OK, let's do it.
	*/
	spin_lock_irqsave(&dev->spinlock, flags);
	INIT_LIST_HEAD(&dev->sio_avail);
	INIT_LIST_HEAD(&dev->sio_full);
	nbufs = dev->n_sbufs;
	dev->n_sbufs = 0;
	spin_unlock_irqrestore(&dev->spinlock, flags);
	for (i = 0; i < nbufs; i++) {
		if (dev->sio_bufs[i].buffer != NULL)
			vfree(dev->sio_bufs[i].buffer);
	}
	kfree(dev->sio_bufs);
	dev->sio_bufs = NULL;
	return 0;
}