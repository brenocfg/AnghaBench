#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct chp_id {size_t cssid; size_t id; } ;
struct TYPE_9__ {int /*<<< orphan*/  kobj; int /*<<< orphan*/  release; int /*<<< orphan*/ * parent; } ;
struct TYPE_8__ {int flags; } ;
struct channel_path {int state; int cmg; TYPE_2__ dev; TYPE_1__ desc; int /*<<< orphan*/  lock; struct chp_id chpid; } ;
struct TYPE_11__ {int /*<<< orphan*/  mutex; struct channel_path** chps; scalar_t__ cm_enabled; int /*<<< orphan*/  device; } ;
struct TYPE_10__ {scalar_t__ secm; scalar_t__ scmc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_MSG_EVENT (int /*<<< orphan*/ ,char*,size_t,size_t,int) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_7__** channel_subsystems ; 
 int chp_add_cmg_attr (struct channel_path*) ; 
 int /*<<< orphan*/  chp_attr_group ; 
 scalar_t__ chp_is_registered (struct chp_id) ; 
 int /*<<< orphan*/  chp_release ; 
 int chp_update_desc (struct channel_path*) ; 
 int chsc_get_channel_measurement_chars (struct channel_path*) ; 
 TYPE_6__ css_chsc_characteristics ; 
 int /*<<< orphan*/  dev_set_name (TYPE_2__*,char*,size_t,size_t) ; 
 int device_register (TYPE_2__*) ; 
 int /*<<< orphan*/  device_unregister (TYPE_2__*) ; 
 int /*<<< orphan*/  kfree (struct channel_path*) ; 
 struct channel_path* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (TYPE_2__*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int chp_new(struct chp_id chpid)
{
	struct channel_path *chp;
	int ret;

	if (chp_is_registered(chpid))
		return 0;
	chp = kzalloc(sizeof(struct channel_path), GFP_KERNEL);
	if (!chp)
		return -ENOMEM;

	/* fill in status, etc. */
	chp->chpid = chpid;
	chp->state = 1;
	chp->dev.parent = &channel_subsystems[chpid.cssid]->device;
	chp->dev.release = chp_release;
	mutex_init(&chp->lock);

	/* Obtain channel path description and fill it in. */
	ret = chp_update_desc(chp);
	if (ret)
		goto out_free;
	if ((chp->desc.flags & 0x80) == 0) {
		ret = -ENODEV;
		goto out_free;
	}
	/* Get channel-measurement characteristics. */
	if (css_chsc_characteristics.scmc && css_chsc_characteristics.secm) {
		ret = chsc_get_channel_measurement_chars(chp);
		if (ret)
			goto out_free;
	} else {
		chp->cmg = -1;
	}
	dev_set_name(&chp->dev, "chp%x.%02x", chpid.cssid, chpid.id);

	/* make it known to the system */
	ret = device_register(&chp->dev);
	if (ret) {
		CIO_MSG_EVENT(0, "Could not register chp%x.%02x: %d\n",
			      chpid.cssid, chpid.id, ret);
		put_device(&chp->dev);
		goto out;
	}
	ret = sysfs_create_group(&chp->dev.kobj, &chp_attr_group);
	if (ret) {
		device_unregister(&chp->dev);
		goto out;
	}
	mutex_lock(&channel_subsystems[chpid.cssid]->mutex);
	if (channel_subsystems[chpid.cssid]->cm_enabled) {
		ret = chp_add_cmg_attr(chp);
		if (ret) {
			sysfs_remove_group(&chp->dev.kobj, &chp_attr_group);
			device_unregister(&chp->dev);
			mutex_unlock(&channel_subsystems[chpid.cssid]->mutex);
			goto out;
		}
	}
	channel_subsystems[chpid.cssid]->chps[chpid.id] = chp;
	mutex_unlock(&channel_subsystems[chpid.cssid]->mutex);
	goto out;
out_free:
	kfree(chp);
out:
	return ret;
}