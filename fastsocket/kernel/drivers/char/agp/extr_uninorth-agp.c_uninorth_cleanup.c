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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int UNI_N_CFG_GART_2xRESET ; 
 int /*<<< orphan*/  UNI_N_CFG_GART_CTRL ; 
 int UNI_N_CFG_GART_ENABLE ; 
 int UNI_N_CFG_GART_INVAL ; 
 TYPE_1__* agp_bridge ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int uninorth_rev ; 

__attribute__((used)) static void uninorth_cleanup(void)
{
	u32 tmp;

	pci_read_config_dword(agp_bridge->dev, UNI_N_CFG_GART_CTRL, &tmp);
	if (!(tmp & UNI_N_CFG_GART_ENABLE))
		return;
	tmp |= UNI_N_CFG_GART_INVAL;
	pci_write_config_dword(agp_bridge->dev, UNI_N_CFG_GART_CTRL, tmp);
	pci_write_config_dword(agp_bridge->dev, UNI_N_CFG_GART_CTRL, 0);

	if (uninorth_rev <= 0x30) {
		pci_write_config_dword(agp_bridge->dev, UNI_N_CFG_GART_CTRL,
				       UNI_N_CFG_GART_2xRESET);
		pci_write_config_dword(agp_bridge->dev, UNI_N_CFG_GART_CTRL,
				       0);
	}
}