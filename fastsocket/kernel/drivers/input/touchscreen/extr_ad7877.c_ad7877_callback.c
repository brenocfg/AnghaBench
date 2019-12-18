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
struct ad7877 {int /*<<< orphan*/  lock; int /*<<< orphan*/  timer; scalar_t__ pending; } ;

/* Variables and functions */
 scalar_t__ TS_PEN_UP_TIMEOUT ; 
 int /*<<< orphan*/  ad7877_rx (struct ad7877*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ad7877_callback(void *_ts)
{
	struct ad7877 *ts = _ts;

	spin_lock_irq(&ts->lock);

	ad7877_rx(ts);
	ts->pending = 0;
	mod_timer(&ts->timer, jiffies + TS_PEN_UP_TIMEOUT);

	spin_unlock_irq(&ts->lock);
}