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
struct cfg80211_registered_device {int /*<<< orphan*/  bss_tree; int /*<<< orphan*/  bss_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  hidden_beacon_bss; } ;
struct cfg80211_internal_bss {int /*<<< orphan*/  rbn; int /*<<< orphan*/  list; int /*<<< orphan*/  hidden_list; TYPE_1__ pub; } ;

/* Variables and functions */
 int /*<<< orphan*/  bss_ref_put (struct cfg80211_registered_device*,struct cfg80211_internal_bss*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool __cfg80211_unlink_bss(struct cfg80211_registered_device *dev,
				  struct cfg80211_internal_bss *bss)
{
	lockdep_assert_held(&dev->bss_lock);

	if (!list_empty(&bss->hidden_list)) {
		/*
		 * don't remove the beacon entry if it has
		 * probe responses associated with it
		 */
		if (!bss->pub.hidden_beacon_bss)
			return false;
		/*
		 * if it's a probe response entry break its
		 * link to the other entries in the group
		 */
		list_del_init(&bss->hidden_list);
	}

	list_del_init(&bss->list);
	rb_erase(&bss->rbn, &dev->bss_tree);
	bss_ref_put(dev, bss);
	return true;
}