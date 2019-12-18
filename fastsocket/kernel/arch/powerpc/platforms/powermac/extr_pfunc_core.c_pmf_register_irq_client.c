#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pmf_irq_client {struct pmf_function* func; int /*<<< orphan*/  link; } ;
struct pmf_function {int /*<<< orphan*/  irq_clients; TYPE_2__* dev; } ;
struct device_node {int dummy; } ;
struct TYPE_4__ {TYPE_1__* handlers; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* irq_enable ) (struct pmf_function*) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  PMF_FLAGS_INT_GEN ; 
 struct pmf_function* __pmf_find_function (struct device_node*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct pmf_function* pmf_get_function (struct pmf_function*) ; 
 int /*<<< orphan*/  pmf_irq_mutex ; 
 int /*<<< orphan*/  pmf_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct pmf_function*) ; 

int pmf_register_irq_client(struct device_node *target,
			    const char *name,
			    struct pmf_irq_client *client)
{
	struct pmf_function *func;
	unsigned long flags;

	spin_lock_irqsave(&pmf_lock, flags);
	func = __pmf_find_function(target, name, PMF_FLAGS_INT_GEN);
	if (func)
		func = pmf_get_function(func);
	spin_unlock_irqrestore(&pmf_lock, flags);
	if (func == NULL)
		return -ENODEV;

	/* guard against manipulations of list */
	mutex_lock(&pmf_irq_mutex);
	if (list_empty(&func->irq_clients))
		func->dev->handlers->irq_enable(func);

	/* guard against pmf_do_irq while changing list */
	spin_lock_irqsave(&pmf_lock, flags);
	list_add(&client->link, &func->irq_clients);
	spin_unlock_irqrestore(&pmf_lock, flags);

	client->func = func;
	mutex_unlock(&pmf_irq_mutex);

	return 0;
}