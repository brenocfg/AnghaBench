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
struct TYPE_2__ {unsigned long data; int /*<<< orphan*/  function; } ;
struct led_timer {int /*<<< orphan*/  list; TYPE_1__ blink_timer; struct led_classdev* cdev; } ;
struct led_classdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  init_timer (TYPE_1__*) ; 
 struct led_timer* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  led_lock ; 
 int /*<<< orphan*/  led_timer_function ; 
 int /*<<< orphan*/  led_timers ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct led_timer *led_new_timer(struct led_classdev *led_cdev)
{
	struct led_timer *led;
	unsigned long flags;

	led = kzalloc(sizeof(struct led_timer), GFP_ATOMIC);
	if (!led)
		return NULL;

	led->cdev = led_cdev;
	init_timer(&led->blink_timer);
	led->blink_timer.function = led_timer_function;
	led->blink_timer.data = (unsigned long) led;

	spin_lock_irqsave(&led_lock, flags);
	list_add(&led->list, &led_timers);
	spin_unlock_irqrestore(&led_lock, flags);

	return led;
}