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
struct ieee80211_device {int /*<<< orphan*/  start_ibss_wq; int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

inline void ieee80211_start_ibss(struct ieee80211_device *ieee)
{
	queue_delayed_work(ieee->wq, &ieee->start_ibss_wq, 150);
}