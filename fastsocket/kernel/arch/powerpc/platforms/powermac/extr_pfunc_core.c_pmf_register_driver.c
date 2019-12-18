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
struct pmf_handlers {int dummy; } ;
struct pmf_device {int /*<<< orphan*/  link; int /*<<< orphan*/  functions; struct pmf_handlers* handlers; int /*<<< orphan*/  node; int /*<<< orphan*/  ref; } ;
struct device_node {int /*<<< orphan*/  full_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,...) ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct pmf_device*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct pmf_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_get (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int pmf_add_functions (struct pmf_device*,void*) ; 
 int /*<<< orphan*/  pmf_devices ; 
 struct pmf_device* pmf_find_device (struct device_node*) ; 
 int /*<<< orphan*/  pmf_lock ; 
 int /*<<< orphan*/  pmf_put_device (struct pmf_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int pmf_register_driver(struct device_node *np,
			struct pmf_handlers *handlers,
			void *driverdata)
{
	struct pmf_device *dev;
	unsigned long flags;
	int rc = 0;

	if (handlers == NULL)
		return -EINVAL;

	DBG("pmf: registering driver for node %s\n", np->full_name);

	spin_lock_irqsave(&pmf_lock, flags);
	dev = pmf_find_device(np);
	spin_unlock_irqrestore(&pmf_lock, flags);
	if (dev != NULL) {
		DBG("pmf: already there !\n");
		pmf_put_device(dev);
		return -EBUSY;
	}

	dev = kzalloc(sizeof(struct pmf_device), GFP_KERNEL);
	if (dev == NULL) {
		DBG("pmf: no memory !\n");
		return -ENOMEM;
	}
	kref_init(&dev->ref);
	dev->node = of_node_get(np);
	dev->handlers = handlers;
	INIT_LIST_HEAD(&dev->functions);

	rc = pmf_add_functions(dev, driverdata);
	if (rc == 0) {
		DBG("pmf: no functions, disposing.. \n");
		of_node_put(np);
		kfree(dev);
		return -ENODEV;
	}

	spin_lock_irqsave(&pmf_lock, flags);
	list_add(&dev->link, &pmf_devices);
	spin_unlock_irqrestore(&pmf_lock, flags);

	return 0;
}