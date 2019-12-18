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
struct b43legacy_wldev {int /*<<< orphan*/  restart_work; TYPE_1__* wl; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 scalar_t__ B43legacy_STAT_INITIALIZED ; 
 scalar_t__ b43legacy_status (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacyinfo (TYPE_1__*,char*,char const*) ; 
 int /*<<< orphan*/  ieee80211_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void b43legacy_controller_restart(struct b43legacy_wldev *dev,
				  const char *reason)
{
	/* Must avoid requeueing, if we are in shutdown. */
	if (b43legacy_status(dev) < B43legacy_STAT_INITIALIZED)
		return;
	b43legacyinfo(dev->wl, "Controller RESET (%s) ...\n", reason);
	ieee80211_queue_work(dev->wl->hw, &dev->restart_work);
}