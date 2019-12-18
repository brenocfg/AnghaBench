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
struct rt2x00_dev {scalar_t__ intf_associated; scalar_t__ intf_sta_count; scalar_t__ intf_ap_count; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_STATE_STARTED ; 
 int /*<<< orphan*/  rt2x00lib_disable_radio (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void rt2x00lib_stop(struct rt2x00_dev *rt2x00dev)
{
	if (!test_and_clear_bit(DEVICE_STATE_STARTED, &rt2x00dev->flags))
		return;

	/*
	 * Perhaps we can add something smarter here,
	 * but for now just disabling the radio should do.
	 */
	rt2x00lib_disable_radio(rt2x00dev);

	rt2x00dev->intf_ap_count = 0;
	rt2x00dev->intf_sta_count = 0;
	rt2x00dev->intf_associated = 0;
}