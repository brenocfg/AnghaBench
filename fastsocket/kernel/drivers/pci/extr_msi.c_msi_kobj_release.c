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
struct msi_desc {int /*<<< orphan*/  dev; } ;
struct kobject {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_dev_put (int /*<<< orphan*/ ) ; 
 struct msi_desc* to_msi_desc (struct kobject*) ; 

void msi_kobj_release(struct kobject *kobj)
{
	struct msi_desc *entry = to_msi_desc(kobj);

	pci_dev_put(entry->dev);
}