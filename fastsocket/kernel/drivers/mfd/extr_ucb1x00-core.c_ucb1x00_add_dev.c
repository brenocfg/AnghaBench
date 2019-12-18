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
struct ucb1x00_driver {int (* add ) (struct ucb1x00_dev*) ;int /*<<< orphan*/  devs; } ;
struct ucb1x00_dev {int /*<<< orphan*/  drv_node; int /*<<< orphan*/  dev_node; struct ucb1x00_driver* drv; struct ucb1x00* ucb; } ;
struct ucb1x00 {int /*<<< orphan*/  devs; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct ucb1x00_dev*) ; 
 struct ucb1x00_dev* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int stub1 (struct ucb1x00_dev*) ; 

__attribute__((used)) static int ucb1x00_add_dev(struct ucb1x00 *ucb, struct ucb1x00_driver *drv)
{
	struct ucb1x00_dev *dev;
	int ret = -ENOMEM;

	dev = kmalloc(sizeof(struct ucb1x00_dev), GFP_KERNEL);
	if (dev) {
		dev->ucb = ucb;
		dev->drv = drv;

		ret = drv->add(dev);

		if (ret == 0) {
			list_add(&dev->dev_node, &ucb->devs);
			list_add(&dev->drv_node, &drv->devs);
		} else {
			kfree(dev);
		}
	}
	return ret;
}