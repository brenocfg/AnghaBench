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
struct stripe_head {int dummy; } ;
struct r5conf {int /*<<< orphan*/  device_lock; } ;

/* Variables and functions */
 int MAX_STRIPE_BATCH ; 
 struct stripe_head* __get_priority_stripe (struct r5conf*) ; 
 int /*<<< orphan*/  __release_stripe (struct r5conf*,struct stripe_head*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  handle_stripe (struct stripe_head*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int handle_active_stripes(struct r5conf *conf)
{
	struct stripe_head *batch[MAX_STRIPE_BATCH], *sh;
	int i, batch_size = 0;

	while (batch_size < MAX_STRIPE_BATCH &&
			(sh = __get_priority_stripe(conf)) != NULL)
		batch[batch_size++] = sh;

	if (batch_size == 0)
		return batch_size;
	spin_unlock_irq(&conf->device_lock);

	for (i = 0; i < batch_size; i++)
		handle_stripe(batch[i]);

	cond_resched();

	spin_lock_irq(&conf->device_lock);
	for (i = 0; i < batch_size; i++)
		__release_stripe(conf, batch[i]);
	return batch_size;
}