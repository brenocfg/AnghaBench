#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct notifier_block {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
struct TYPE_5__ {unsigned long misc; } ;
struct TYPE_6__ {TYPE_1__ ctrl; } ;
struct TYPE_7__ {TYPE_2__ perif; } ;

/* Variables and functions */
 unsigned long MACEISA_LED_GREEN ; 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  PANIC_FREQ ; 
 int /*<<< orphan*/  blink_timeout (int /*<<< orphan*/ ) ; 
 TYPE_4__ blink_timer ; 
 int has_panicked ; 
 TYPE_3__* mace ; 

__attribute__((used)) static int panic_event(struct notifier_block *this, unsigned long event,
		       void *ptr)
{
	unsigned long led;

	if (has_panicked)
		return NOTIFY_DONE;
	has_panicked = 1;

	/* turn off the green LED */
	led = mace->perif.ctrl.misc | MACEISA_LED_GREEN;
	mace->perif.ctrl.misc = led;

	blink_timer.data = PANIC_FREQ;
	blink_timeout(PANIC_FREQ);

	return NOTIFY_DONE;
}