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
struct pnp_id {int /*<<< orphan*/  id; struct pnp_id* next; } ;
struct pnp_dev {scalar_t__ active; TYPE_1__* protocol; int /*<<< orphan*/  dev; struct pnp_id* id; scalar_t__ card; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int __pnp_add_device (struct pnp_dev*) ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ scnprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

int pnp_add_device(struct pnp_dev *dev)
{
	int ret;
	char buf[128];
	int len = 0;
	struct pnp_id *id;

	if (dev->card)
		return -EINVAL;

	ret = __pnp_add_device(dev);
	if (ret)
		return ret;

	buf[0] = '\0';
	for (id = dev->id; id; id = id->next)
		len += scnprintf(buf + len, sizeof(buf) - len, " %s", id->id);

	dev_printk(KERN_DEBUG, &dev->dev, "%s device, IDs%s (%s)\n",
		   dev->protocol->name, buf,
		   dev->active ? "active" : "disabled");
	return 0;
}