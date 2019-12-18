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
struct ad7879 {int /*<<< orphan*/  mutex; TYPE_1__* bus; scalar_t__ disabled; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ad7879_setup (struct ad7879*) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ad7879_enable(struct ad7879 *ts)
{
	mutex_lock(&ts->mutex);

	if (ts->disabled) {
		ad7879_setup(ts);
		ts->disabled = 0;
		enable_irq(ts->bus->irq);
	}

	mutex_unlock(&ts->mutex);
}