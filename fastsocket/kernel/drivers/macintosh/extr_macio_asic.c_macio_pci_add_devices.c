#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_6__ {struct device dev; struct device_node* node; } ;
struct macio_dev {TYPE_3__ ofdev; struct resource* resource; } ;
struct TYPE_5__ {TYPE_1__* pdev; } ;
struct macio_chip {struct device_node* of_node; TYPE_2__ lbus; } ;
struct device_node {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {struct resource* resource; struct device dev; } ;

/* Variables and functions */
 struct resource iomem_resource ; 
 struct macio_dev* macio_add_one_device (struct macio_chip*,struct device*,struct device_node*,struct macio_dev*,struct resource*) ; 
 scalar_t__ macio_skip_device (struct device_node*) ; 
 struct device_node* of_get_next_child (struct device_node*,struct device_node*) ; 
 struct device_node* of_node_get (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void macio_pci_add_devices(struct macio_chip *chip)
{
	struct device_node *np, *pnode;
	struct macio_dev *rdev, *mdev, *mbdev = NULL, *sdev = NULL;
	struct device *parent = NULL;
	struct resource *root_res = &iomem_resource;
	
	/* Add a node for the macio bus itself */
#ifdef CONFIG_PCI
	if (chip->lbus.pdev) {
		parent = &chip->lbus.pdev->dev;
		root_res = &chip->lbus.pdev->resource[0];
	}
#endif
	pnode = of_node_get(chip->of_node);
	if (pnode == NULL)
		return;

	/* Add macio itself to hierarchy */
	rdev = macio_add_one_device(chip, parent, pnode, NULL, root_res);
	if (rdev == NULL)
		return;
	root_res = &rdev->resource[0];

	/* First scan 1st level */
	for (np = NULL; (np = of_get_next_child(pnode, np)) != NULL;) {
		if (macio_skip_device(np))
			continue;
		of_node_get(np);
		mdev = macio_add_one_device(chip, &rdev->ofdev.dev, np, NULL,
					    root_res);
		if (mdev == NULL)
			of_node_put(np);
		else if (strncmp(np->name, "media-bay", 9) == 0)
			mbdev = mdev;
		else if (strncmp(np->name, "escc", 4) == 0)
			sdev = mdev;
	}

	/* Add media bay devices if any */
	if (mbdev)
		for (np = NULL; (np = of_get_next_child(mbdev->ofdev.node, np))
			     != NULL;) {
			if (macio_skip_device(np))
				continue;
			of_node_get(np);
			if (macio_add_one_device(chip, &mbdev->ofdev.dev, np,
						 mbdev,  root_res) == NULL)
				of_node_put(np);
		}

	/* Add serial ports if any */
	if (sdev) {
		for (np = NULL; (np = of_get_next_child(sdev->ofdev.node, np))
			     != NULL;) {
			if (macio_skip_device(np))
				continue;
			of_node_get(np);
			if (macio_add_one_device(chip, &sdev->ofdev.dev, np,
						 NULL, root_res) == NULL)
				of_node_put(np);
		}
	}
}