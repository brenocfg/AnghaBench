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
struct wireless_dev {int dummy; } ;
struct wiphy {int dummy; } ;

/* Variables and functions */
 int ieee80211_do_open (struct wireless_dev*,int) ; 

__attribute__((used)) static int ieee80211_start_p2p_device(struct wiphy *wiphy,
				      struct wireless_dev *wdev)
{
	return ieee80211_do_open(wdev, true);
}