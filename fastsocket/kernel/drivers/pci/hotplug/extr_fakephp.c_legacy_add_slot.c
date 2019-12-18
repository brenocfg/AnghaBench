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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct legacy_slot {int /*<<< orphan*/  list; int /*<<< orphan*/  dev; int /*<<< orphan*/  kobj; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ kobject_init_and_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct legacy_slot* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  legacy_ktype ; 
 int /*<<< orphan*/  legacy_list ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_dev_get (struct pci_dev*) ; 
 TYPE_1__* pci_slots_kset ; 

__attribute__((used)) static int legacy_add_slot(struct pci_dev *pdev)
{
	struct legacy_slot *slot = kzalloc(sizeof(*slot), GFP_KERNEL);

	if (!slot)
		return -ENOMEM;

	if (kobject_init_and_add(&slot->kobj, &legacy_ktype,
				 &pci_slots_kset->kobj, "%s",
				 dev_name(&pdev->dev))) {
		dev_warn(&pdev->dev, "Failed to created legacy fake slot\n");
		return -EINVAL;
	}
	slot->dev = pci_dev_get(pdev);

	list_add(&slot->list, &legacy_list);

	return 0;
}