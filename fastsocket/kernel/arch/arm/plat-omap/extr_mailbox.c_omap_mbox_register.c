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
struct omap_mbox {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; scalar_t__ next; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_attr_mbox ; 
 int /*<<< orphan*/  device_create (int /*<<< orphan*/ *,struct device*,int /*<<< orphan*/ ,struct omap_mbox*,char*,int /*<<< orphan*/ ) ; 
 int device_create_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ ) ; 
 struct omap_mbox** find_mboxes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mboxes_lock ; 
 int /*<<< orphan*/  omap_mbox_class ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

int omap_mbox_register(struct device *parent, struct omap_mbox *mbox)
{
	int ret = 0;
	struct omap_mbox **tmp;

	if (!mbox)
		return -EINVAL;
	if (mbox->next)
		return -EBUSY;

	mbox->dev = device_create(&omap_mbox_class,
				  parent, 0, mbox, "%s", mbox->name);
	if (IS_ERR(mbox->dev))
		return PTR_ERR(mbox->dev);

	ret = device_create_file(mbox->dev, &dev_attr_mbox);
	if (ret)
		goto err_sysfs;

	write_lock(&mboxes_lock);
	tmp = find_mboxes(mbox->name);
	if (*tmp) {
		ret = -EBUSY;
		write_unlock(&mboxes_lock);
		goto err_find;
	}
	*tmp = mbox;
	write_unlock(&mboxes_lock);

	return 0;

err_find:
	device_remove_file(mbox->dev, &dev_attr_mbox);
err_sysfs:
	device_unregister(mbox->dev);
	return ret;
}