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
struct rt2x00_dev {TYPE_1__* hw; int /*<<< orphan*/  cap_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAPABILITY_HW_BUTTON ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wiphy_rfkill_stop_polling (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void rt2x00rfkill_unregister(struct rt2x00_dev *rt2x00dev)
{
	if (test_bit(CAPABILITY_HW_BUTTON, &rt2x00dev->cap_flags))
		wiphy_rfkill_stop_polling(rt2x00dev->hw->wiphy);
}