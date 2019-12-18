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
struct rio_usb_data {int isopen; TYPE_1__* rio_dev; int /*<<< orphan*/  lock; int /*<<< orphan*/  wait_q; int /*<<< orphan*/  present; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct rio_usb_data rio_instance ; 

__attribute__((used)) static int open_rio(struct inode *inode, struct file *file)
{
	struct rio_usb_data *rio = &rio_instance;

	mutex_lock(&(rio->lock));

	if (rio->isopen || !rio->present) {
		mutex_unlock(&(rio->lock));
		return -EBUSY;
	}
	rio->isopen = 1;

	init_waitqueue_head(&rio->wait_q);

	mutex_unlock(&(rio->lock));

	dev_info(&rio->rio_dev->dev, "Rio opened.\n");

	return 0;
}