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
 int OPEN_READ ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 scalar_t__ input_avail () ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  uart6850_input_loop () ; 
 int uart6850_opened ; 
 TYPE_1__ uart6850_timer ; 

__attribute__((used)) static void poll_uart6850(unsigned long dummy)
{
	unsigned long flags;

	if (!(uart6850_opened & OPEN_READ))
		return;		/* Device has been closed */

	spin_lock_irqsave(&lock,flags);
	if (input_avail())
		uart6850_input_loop();

	uart6850_timer.expires = 1 + jiffies;
	add_timer(&uart6850_timer);
	
	/*
	 *	Come back later
	 */

	spin_unlock_irqrestore(&lock,flags);
}