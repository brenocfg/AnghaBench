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
struct clocksource {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __clocksource_change_rating (struct clocksource*,int) ; 
 int /*<<< orphan*/  clocksource_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void clocksource_change_rating(struct clocksource *cs, int rating)
{
	mutex_lock(&clocksource_mutex);
	__clocksource_change_rating(cs, rating);
	mutex_unlock(&clocksource_mutex);
}