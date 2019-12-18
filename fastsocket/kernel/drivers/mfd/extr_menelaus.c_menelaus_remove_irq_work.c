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
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ ** handlers; } ;

/* Variables and functions */
 int menelaus_disable_irq (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* the_menelaus ; 

__attribute__((used)) static int menelaus_remove_irq_work(int irq)
{
	int ret = 0;

	mutex_lock(&the_menelaus->lock);
	ret = menelaus_disable_irq(irq);
	the_menelaus->handlers[irq] = NULL;
	mutex_unlock(&the_menelaus->lock);

	return ret;
}