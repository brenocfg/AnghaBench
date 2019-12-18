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
struct res_counter {struct res_counter* parent; void* soft_limit; void* limit; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 void* RESOURCE_MAX ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void res_counter_init(struct res_counter *counter, struct res_counter *parent)
{
	spin_lock_init(&counter->lock);
	counter->limit = RESOURCE_MAX;
	counter->soft_limit = RESOURCE_MAX;
	counter->parent = parent;
}