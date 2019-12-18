#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct of_device {TYPE_1__ dev; int /*<<< orphan*/ * node; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int device_add (TYPE_1__*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  of_node_to_nid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_dev_node (TYPE_1__*,int /*<<< orphan*/ ) ; 

int of_device_register(struct of_device *ofdev)
{
	BUG_ON(ofdev->node == NULL);

	device_initialize(&ofdev->dev);

	/* device_add will assume that this device is on the same node as
	 * the parent. If there is no parent defined, set the node
	 * explicitly */
	if (!ofdev->dev.parent)
		set_dev_node(&ofdev->dev, of_node_to_nid(ofdev->node));

	return device_add(&ofdev->dev);
}