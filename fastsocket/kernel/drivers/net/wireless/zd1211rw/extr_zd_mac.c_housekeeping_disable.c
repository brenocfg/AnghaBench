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
struct TYPE_2__ {int /*<<< orphan*/  link_led_work; } ;
struct zd_mac {int /*<<< orphan*/  chip; TYPE_1__ housekeeping; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZD_LED_OFF ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg_f (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zd_chip_control_leds (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zd_mac_dev (struct zd_mac*) ; 

__attribute__((used)) static void housekeeping_disable(struct zd_mac *mac)
{
	dev_dbg_f(zd_mac_dev(mac), "\n");
	cancel_delayed_work_sync(&mac->housekeeping.link_led_work);
	zd_chip_control_leds(&mac->chip, ZD_LED_OFF);
}