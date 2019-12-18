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
struct ssb_device {int dummy; } ;
struct b43legacy_wldev {int __using_pio; int /*<<< orphan*/  list; int /*<<< orphan*/  isr_tasklet; int /*<<< orphan*/  bad_frames_preempt; struct b43legacy_wl* wl; struct ssb_device* dev; } ;
struct b43legacy_wl {int /*<<< orphan*/  nr_devs; int /*<<< orphan*/  devlist; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_STAT_UNINIT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  b43legacy_debugfs_add_device (struct b43legacy_wldev*) ; 
 scalar_t__ b43legacy_interrupt_tasklet ; 
 int /*<<< orphan*/  b43legacy_set_status (struct b43legacy_wldev*,int /*<<< orphan*/ ) ; 
 int b43legacy_wireless_core_attach (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  kfree (struct b43legacy_wldev*) ; 
 struct b43legacy_wldev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  modparam_bad_frames_preempt ; 
 scalar_t__ modparam_pio ; 
 int /*<<< orphan*/  ssb_set_drvdata (struct ssb_device*,struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,void (*) (unsigned long),unsigned long) ; 

__attribute__((used)) static int b43legacy_one_core_attach(struct ssb_device *dev,
				     struct b43legacy_wl *wl)
{
	struct b43legacy_wldev *wldev;
	int err = -ENOMEM;

	wldev = kzalloc(sizeof(*wldev), GFP_KERNEL);
	if (!wldev)
		goto out;

	wldev->dev = dev;
	wldev->wl = wl;
	b43legacy_set_status(wldev, B43legacy_STAT_UNINIT);
	wldev->bad_frames_preempt = modparam_bad_frames_preempt;
	tasklet_init(&wldev->isr_tasklet,
		     (void (*)(unsigned long))b43legacy_interrupt_tasklet,
		     (unsigned long)wldev);
	if (modparam_pio)
		wldev->__using_pio = true;
	INIT_LIST_HEAD(&wldev->list);

	err = b43legacy_wireless_core_attach(wldev);
	if (err)
		goto err_kfree_wldev;

	list_add(&wldev->list, &wl->devlist);
	wl->nr_devs++;
	ssb_set_drvdata(dev, wldev);
	b43legacy_debugfs_add_device(wldev);
out:
	return err;

err_kfree_wldev:
	kfree(wldev);
	return err;
}