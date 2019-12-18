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
struct miscdevice {int minor; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int DYNAMIC_MINORS ; 
 int EINVAL ; 
 int /*<<< orphan*/  MISC_MAJOR ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  misc_class ; 
 int* misc_minors ; 
 int /*<<< orphan*/  misc_mtx ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int misc_deregister(struct miscdevice *misc)
{
	int i = misc->minor;

	if (list_empty(&misc->list))
		return -EINVAL;

	mutex_lock(&misc_mtx);
	list_del(&misc->list);
	device_destroy(misc_class, MKDEV(MISC_MAJOR, misc->minor));
	if (i < DYNAMIC_MINORS && i>0) {
		misc_minors[i>>3] &= ~(1 << (misc->minor & 7));
	}
	mutex_unlock(&misc_mtx);
	return 0;
}