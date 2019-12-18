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
struct cx231xx {int /*<<< orphan*/  devlist_count; int /*<<< orphan*/  devlist; int /*<<< orphan*/ * udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cx231xx_devlist_mutex ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void cx231xx_remove_from_devlist(struct cx231xx *dev)
{
	if (dev == NULL)
		return;
	if (dev->udev == NULL)
		return;

	if (atomic_read(&dev->devlist_count) > 0) {
		mutex_lock(&cx231xx_devlist_mutex);
		list_del(&dev->devlist);
		atomic_dec(&dev->devlist_count);
		mutex_unlock(&cx231xx_devlist_mutex);
	}
}