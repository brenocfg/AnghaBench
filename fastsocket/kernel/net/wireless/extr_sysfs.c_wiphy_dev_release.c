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
struct device {int dummy; } ;
struct cfg80211_registered_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfg80211_dev_free (struct cfg80211_registered_device*) ; 
 struct cfg80211_registered_device* dev_to_rdev (struct device*) ; 

__attribute__((used)) static void wiphy_dev_release(struct device *dev)
{
	struct cfg80211_registered_device *rdev = dev_to_rdev(dev);

	cfg80211_dev_free(rdev);
}