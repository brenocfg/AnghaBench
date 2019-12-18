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
struct TYPE_3__ {unsigned long expires; } ;
struct delay_c {int /*<<< orphan*/  timer_lock; TYPE_1__ delay_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  mod_timer (TYPE_1__*,unsigned long) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_pending (TYPE_1__*) ; 

__attribute__((used)) static void queue_timeout(struct delay_c *dc, unsigned long expires)
{
	mutex_lock(&dc->timer_lock);

	if (!timer_pending(&dc->delay_timer) || expires < dc->delay_timer.expires)
		mod_timer(&dc->delay_timer, expires);

	mutex_unlock(&dc->timer_lock);
}