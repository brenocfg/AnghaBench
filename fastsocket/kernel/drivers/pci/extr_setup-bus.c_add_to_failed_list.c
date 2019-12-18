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
struct resource_list_x {int dummy; } ;
struct resource {int dummy; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_to_list (struct resource_list_x*,struct pci_dev*,struct resource*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_to_failed_list(struct resource_list_x *head,
				struct pci_dev *dev, struct resource *res)
{
	add_to_list(head, dev, res, 0);
}