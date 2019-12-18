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
struct cfg80211_registered_device {TYPE_1__* wowlan; } ;
struct TYPE_2__ {int n_patterns; struct TYPE_2__* tcp; scalar_t__ sock; struct TYPE_2__* patterns; struct TYPE_2__* mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  sock_release (scalar_t__) ; 

__attribute__((used)) static inline void
cfg80211_rdev_free_wowlan(struct cfg80211_registered_device *rdev)
{
	int i;

	if (!rdev->wowlan)
		return;
	for (i = 0; i < rdev->wowlan->n_patterns; i++)
		kfree(rdev->wowlan->patterns[i].mask);
	kfree(rdev->wowlan->patterns);
	if (rdev->wowlan->tcp && rdev->wowlan->tcp->sock)
		sock_release(rdev->wowlan->tcp->sock);
	kfree(rdev->wowlan->tcp);
	kfree(rdev->wowlan);
}