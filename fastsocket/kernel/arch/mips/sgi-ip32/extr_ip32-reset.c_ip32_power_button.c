#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  data; } ;
struct TYPE_5__ {scalar_t__ expires; int /*<<< orphan*/  function; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  POWERDOWN_FREQ ; 
 int POWERDOWN_TIMEOUT ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  blink_timeout (int /*<<< orphan*/ ) ; 
 TYPE_3__ blink_timer ; 
 scalar_t__ has_panicked ; 
 int /*<<< orphan*/  init_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  ip32_machine_power_off () ; 
 scalar_t__ jiffies ; 
 scalar_t__ kill_cad_pid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  power_timeout ; 
 TYPE_1__ power_timer ; 
 int shuting_down ; 

__attribute__((used)) static inline void ip32_power_button(void)
{
	if (has_panicked)
		return;

	if (shuting_down || kill_cad_pid(SIGINT, 1)) {
		/* No init process or button pressed twice.  */
		ip32_machine_power_off();
	}

	shuting_down = 1;
	blink_timer.data = POWERDOWN_FREQ;
	blink_timeout(POWERDOWN_FREQ);

	init_timer(&power_timer);
	power_timer.function = power_timeout;
	power_timer.expires = jiffies + POWERDOWN_TIMEOUT * HZ;
	add_timer(&power_timer);
}