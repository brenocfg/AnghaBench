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
struct TYPE_2__ {scalar_t__ applid; } ;
struct capidev {int /*<<< orphan*/  list; int /*<<< orphan*/  ncci_list_mtx; int /*<<< orphan*/  recvqueue; TYPE_1__ ap; } ;

/* Variables and functions */
 int /*<<< orphan*/  capi20_release (TYPE_1__*) ; 
 int /*<<< orphan*/  capidev_list_lock ; 
 int /*<<< orphan*/  capincci_free (struct capidev*,int) ; 
 int /*<<< orphan*/  kfree (struct capidev*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void capidev_free(struct capidev *cdev)
{
	unsigned long flags;

	if (cdev->ap.applid) {
		capi20_release(&cdev->ap);
		cdev->ap.applid = 0;
	}
	skb_queue_purge(&cdev->recvqueue);

	mutex_lock(&cdev->ncci_list_mtx);
	capincci_free(cdev, 0xffffffff);
	mutex_unlock(&cdev->ncci_list_mtx);

	write_lock_irqsave(&capidev_list_lock, flags);
	list_del(&cdev->list);
	write_unlock_irqrestore(&capidev_list_lock, flags);
	kfree(cdev);
}