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
struct rfcomm_dlc {struct rfcomm_dev* owner; } ;
struct rfcomm_dev {int /*<<< orphan*/  id; int /*<<< orphan*/  list; struct rfcomm_dlc* dlc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct rfcomm_dev*,struct rfcomm_dlc*) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  kfree (struct rfcomm_dev*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfcomm_dlc_lock (struct rfcomm_dlc*) ; 
 int /*<<< orphan*/  rfcomm_dlc_put (struct rfcomm_dlc*) ; 
 int /*<<< orphan*/  rfcomm_dlc_unlock (struct rfcomm_dlc*) ; 
 int /*<<< orphan*/  rfcomm_tty_driver ; 
 int /*<<< orphan*/  tty_unregister_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rfcomm_dev_destruct(struct rfcomm_dev *dev)
{
	struct rfcomm_dlc *dlc = dev->dlc;

	BT_DBG("dev %p dlc %p", dev, dlc);

	/* Refcount should only hit zero when called from rfcomm_dev_del()
	   which will have taken us off the list. Everything else are
	   refcounting bugs. */
	BUG_ON(!list_empty(&dev->list));

	rfcomm_dlc_lock(dlc);
	/* Detach DLC if it's owned by this dev */
	if (dlc->owner == dev)
		dlc->owner = NULL;
	rfcomm_dlc_unlock(dlc);

	rfcomm_dlc_put(dlc);

	tty_unregister_device(rfcomm_tty_driver, dev->id);

	kfree(dev);

	/* It's safe to call module_put() here because socket still
	   holds reference to this module. */
	module_put(THIS_MODULE);
}