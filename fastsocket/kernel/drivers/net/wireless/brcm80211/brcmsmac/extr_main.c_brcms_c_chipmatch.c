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
struct bcma_device {TYPE_1__* bus; } ;
struct TYPE_2__ {int hosttype; } ;

/* Variables and functions */
#define  BCMA_HOSTTYPE_PCI 129 
#define  BCMA_HOSTTYPE_SOC 128 
 int brcms_c_chipmatch_pci (struct bcma_device*) ; 
 int brcms_c_chipmatch_soc (struct bcma_device*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

bool brcms_c_chipmatch(struct bcma_device *core)
{
	switch (core->bus->hosttype) {
	case BCMA_HOSTTYPE_PCI:
		return brcms_c_chipmatch_pci(core);
	case BCMA_HOSTTYPE_SOC:
		return brcms_c_chipmatch_soc(core);
	default:
		pr_err("unknown host type: %i\n", core->bus->hosttype);
		return false;
	}
}