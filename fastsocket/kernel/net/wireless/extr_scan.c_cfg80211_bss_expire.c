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
struct cfg80211_registered_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_SCAN_RESULT_EXPIRE ; 
 int /*<<< orphan*/  __cfg80211_bss_expire (struct cfg80211_registered_device*,scalar_t__) ; 
 scalar_t__ jiffies ; 

void cfg80211_bss_expire(struct cfg80211_registered_device *dev)
{
	__cfg80211_bss_expire(dev, jiffies - IEEE80211_SCAN_RESULT_EXPIRE);
}