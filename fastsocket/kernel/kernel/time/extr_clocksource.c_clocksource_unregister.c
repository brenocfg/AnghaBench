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
struct clocksource {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  clocksource_dequeue_watchdog (struct clocksource*) ; 
 int /*<<< orphan*/  clocksource_mutex ; 
 int /*<<< orphan*/  clocksource_select () ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void clocksource_unregister(struct clocksource *cs)
{
	mutex_lock(&clocksource_mutex);
	clocksource_dequeue_watchdog(cs);
	list_del(&cs->list);
	clocksource_select();
	mutex_unlock(&clocksource_mutex);
}