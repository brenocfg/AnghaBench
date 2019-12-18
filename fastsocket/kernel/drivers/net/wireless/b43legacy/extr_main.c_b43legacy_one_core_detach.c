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
struct b43legacy_wldev {int /*<<< orphan*/  list; struct b43legacy_wl* wl; } ;
struct b43legacy_wl {int /*<<< orphan*/  nr_devs; } ;

/* Variables and functions */
 int /*<<< orphan*/  b43legacy_debugfs_remove_device (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_wireless_core_detach (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  kfree (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct b43legacy_wldev* ssb_get_drvdata (struct ssb_device*) ; 
 int /*<<< orphan*/  ssb_set_drvdata (struct ssb_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void b43legacy_one_core_detach(struct ssb_device *dev)
{
	struct b43legacy_wldev *wldev;
	struct b43legacy_wl *wl;

	/* Do not cancel ieee80211-workqueue based work here.
	 * See comment in b43legacy_remove(). */

	wldev = ssb_get_drvdata(dev);
	wl = wldev->wl;
	b43legacy_debugfs_remove_device(wldev);
	b43legacy_wireless_core_detach(wldev);
	list_del(&wldev->list);
	wl->nr_devs--;
	ssb_set_drvdata(dev, NULL);
	kfree(wldev);
}