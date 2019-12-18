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
typedef  int u64 ;
struct wireless_dev {int /*<<< orphan*/  wiphy; scalar_t__ identifier; } ;
struct TYPE_2__ {scalar_t__ wiphy_idx; } ;

/* Variables and functions */
 TYPE_1__* wiphy_to_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u64 wdev_id(struct wireless_dev *wdev)
{
	return (u64)wdev->identifier |
	       ((u64)wiphy_to_dev(wdev->wiphy)->wiphy_idx << 32);
}