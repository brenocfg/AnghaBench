#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {scalar_t__ bus; } ;
struct TYPE_3__ {scalar_t__ bus; } ;

/* Variables and functions */
 TYPE_1__* pmac_agp_bridge ; 
 int /*<<< orphan*/  pmac_agp_suspend (TYPE_1__*) ; 

void pmac_suspend_agp_for_card(struct pci_dev *dev)
{
	if (pmac_agp_bridge == NULL || pmac_agp_suspend == NULL)
		return;
	if (pmac_agp_bridge->bus != dev->bus)
		return;
	pmac_agp_suspend(pmac_agp_bridge);
}