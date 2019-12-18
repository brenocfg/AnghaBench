#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ expires; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  N2100_POWER_BUTTON ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  ctrl_alt_del () ; 
 scalar_t__ gpio_line_get (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 TYPE_1__ power_button_poll_timer ; 

__attribute__((used)) static void power_button_poll(unsigned long dummy)
{
	if (gpio_line_get(N2100_POWER_BUTTON) == 0) {
		ctrl_alt_del();
		return;
	}

	power_button_poll_timer.expires = jiffies + (HZ / 10);
	add_timer(&power_button_poll_timer);
}