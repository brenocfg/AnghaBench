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
struct async_domain {scalar_t__ registered; int /*<<< orphan*/  domain; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  async_lock ; 
 int /*<<< orphan*/  async_register_mutex ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void async_unregister_domain(struct async_domain *domain)
{
	mutex_lock(&async_register_mutex);
	spin_lock_irq(&async_lock);
	WARN_ON(!domain->registered || !list_empty(&domain->node) ||
		!list_empty(&domain->domain));
	domain->registered = 0;
	spin_unlock_irq(&async_lock);
	mutex_unlock(&async_register_mutex);
}