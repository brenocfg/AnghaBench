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
struct b43_wldev {int /*<<< orphan*/  list; int /*<<< orphan*/  bad_frames_preempt; struct b43_wl* wl; struct b43_bus_dev* dev; int /*<<< orphan*/  use_pio; } ;
struct b43_wl {int /*<<< orphan*/  nr_devs; int /*<<< orphan*/  devlist; } ;
struct b43_bus_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_STAT_UNINIT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  b43_bus_set_wldev (struct b43_bus_dev*,struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_debugfs_add_device (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_modparam_pio ; 
 int /*<<< orphan*/  b43_set_status (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int b43_wireless_core_attach (struct b43_wldev*) ; 
 int /*<<< orphan*/  kfree (struct b43_wldev*) ; 
 struct b43_wldev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  modparam_bad_frames_preempt ; 

__attribute__((used)) static int b43_one_core_attach(struct b43_bus_dev *dev, struct b43_wl *wl)
{
	struct b43_wldev *wldev;
	int err = -ENOMEM;

	wldev = kzalloc(sizeof(*wldev), GFP_KERNEL);
	if (!wldev)
		goto out;

	wldev->use_pio = b43_modparam_pio;
	wldev->dev = dev;
	wldev->wl = wl;
	b43_set_status(wldev, B43_STAT_UNINIT);
	wldev->bad_frames_preempt = modparam_bad_frames_preempt;
	INIT_LIST_HEAD(&wldev->list);

	err = b43_wireless_core_attach(wldev);
	if (err)
		goto err_kfree_wldev;

	list_add(&wldev->list, &wl->devlist);
	wl->nr_devs++;
	b43_bus_set_wldev(dev, wldev);
	b43_debugfs_add_device(wldev);

      out:
	return err;

      err_kfree_wldev:
	kfree(wldev);
	return err;
}