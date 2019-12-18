#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int bus_addr; } ;
struct TYPE_7__ {int gart_vm_start; int gart_size; TYPE_1__ gart_info; } ;
typedef  TYPE_2__ drm_radeon_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int,long,int) ; 
 int /*<<< orphan*/  RADEON_PCIE_TX_DISCARD_RD_ADDR_LO ; 
 int /*<<< orphan*/  RADEON_PCIE_TX_GART_BASE ; 
 int /*<<< orphan*/  RADEON_PCIE_TX_GART_CNTL ; 
 int RADEON_PCIE_TX_GART_EN ; 
 int /*<<< orphan*/  RADEON_PCIE_TX_GART_END_LO ; 
 int /*<<< orphan*/  RADEON_PCIE_TX_GART_START_LO ; 
 int RADEON_READ_PCIE (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RADEON_WRITE_PCIE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  radeon_write_agp_location (TYPE_2__*,int) ; 

__attribute__((used)) static void radeon_set_pciegart(drm_radeon_private_t * dev_priv, int on)
{
	u32 tmp = RADEON_READ_PCIE(dev_priv, RADEON_PCIE_TX_GART_CNTL);
	if (on) {

		DRM_DEBUG("programming pcie %08X %08lX %08X\n",
			  dev_priv->gart_vm_start,
			  (long)dev_priv->gart_info.bus_addr,
			  dev_priv->gart_size);
		RADEON_WRITE_PCIE(RADEON_PCIE_TX_DISCARD_RD_ADDR_LO,
				  dev_priv->gart_vm_start);
		RADEON_WRITE_PCIE(RADEON_PCIE_TX_GART_BASE,
				  dev_priv->gart_info.bus_addr);
		RADEON_WRITE_PCIE(RADEON_PCIE_TX_GART_START_LO,
				  dev_priv->gart_vm_start);
		RADEON_WRITE_PCIE(RADEON_PCIE_TX_GART_END_LO,
				  dev_priv->gart_vm_start +
				  dev_priv->gart_size - 1);

		radeon_write_agp_location(dev_priv, 0xffffffc0); /* ?? */

		RADEON_WRITE_PCIE(RADEON_PCIE_TX_GART_CNTL,
				  RADEON_PCIE_TX_GART_EN);
	} else {
		RADEON_WRITE_PCIE(RADEON_PCIE_TX_GART_CNTL,
				  tmp & ~RADEON_PCIE_TX_GART_EN);
	}
}