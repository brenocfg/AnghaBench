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
struct omap_mbox {struct omap_mbox* next; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_attr_mbox ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ ) ; 
 struct omap_mbox* mboxes ; 
 int /*<<< orphan*/  mboxes_lock ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

int omap_mbox_unregister(struct omap_mbox *mbox)
{
	struct omap_mbox **tmp;

	write_lock(&mboxes_lock);
	tmp = &mboxes;
	while (*tmp) {
		if (mbox == *tmp) {
			*tmp = mbox->next;
			mbox->next = NULL;
			write_unlock(&mboxes_lock);
			device_remove_file(mbox->dev, &dev_attr_mbox);
			device_unregister(mbox->dev);
			return 0;
		}
		tmp = &(*tmp)->next;
	}
	write_unlock(&mboxes_lock);

	return -EINVAL;
}