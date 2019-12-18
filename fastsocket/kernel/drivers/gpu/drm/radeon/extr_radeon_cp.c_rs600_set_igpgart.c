#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int bus_addr; } ;
struct TYPE_6__ {int gart_vm_start; int gart_size; TYPE_1__ gart_info; } ;
typedef  TYPE_2__ drm_radeon_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int,long,int) ; 
 int IGP_READ_MCIND (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  IGP_WRITE_MCIND (scalar_t__,int) ; 
 int RS600_EFFECTIVE_L1_CACHE_SIZE (int) ; 
 int RS600_EFFECTIVE_L1_QUEUE_SIZE (int) ; 
 int RS600_EFFECTIVE_L2_CACHE_SIZE (int) ; 
 int RS600_EFFECTIVE_L2_QUEUE_SIZE (int) ; 
 int RS600_ENABLE_FRAGMENT_PROCESSING ; 
 int RS600_ENABLE_PAGE_TABLE ; 
 int RS600_ENABLE_PAGE_TABLES ; 
 int RS600_ENABLE_PT ; 
 int RS600_ENABLE_TRANSLATION_MODE_OVERRIDE ; 
 int RS600_INVALIDATE_ALL_L1_TLBS ; 
 int RS600_INVALIDATE_L2_CACHE ; 
 scalar_t__ RS600_MC_CNTL1 ; 
 scalar_t__ RS600_MC_PT0_CLIENT0_CNTL ; 
 scalar_t__ RS600_MC_PT0_CNTL ; 
 scalar_t__ RS600_MC_PT0_CONTEXT0_CNTL ; 
 scalar_t__ RS600_MC_PT0_CONTEXT0_DEFAULT_READ_ADDR ; 
 scalar_t__ RS600_MC_PT0_CONTEXT0_FLAT_BASE_ADDR ; 
 scalar_t__ RS600_MC_PT0_CONTEXT0_FLAT_END_ADDR ; 
 scalar_t__ RS600_MC_PT0_CONTEXT0_FLAT_START_ADDR ; 
 scalar_t__ RS600_MC_PT0_SYSTEM_APERTURE_HIGH_ADDR ; 
 scalar_t__ RS600_MC_PT0_SYSTEM_APERTURE_LOW_ADDR ; 
 int RS600_PAGE_TABLE_TYPE_FLAT ; 
 int RS600_SYSTEM_ACCESS_MODE_IN_SYS ; 
 int RS600_SYSTEM_APERTURE_UNMAPPED_ACCESS_PASSTHROUGH ; 

__attribute__((used)) static void rs600_set_igpgart(drm_radeon_private_t *dev_priv, int on)
{
	u32 temp;
	int i;

	if (on) {
		DRM_DEBUG("programming igp gart %08X %08lX %08X\n",
			 dev_priv->gart_vm_start,
			 (long)dev_priv->gart_info.bus_addr,
			 dev_priv->gart_size);

		IGP_WRITE_MCIND(RS600_MC_PT0_CNTL, (RS600_EFFECTIVE_L2_CACHE_SIZE(6) |
						    RS600_EFFECTIVE_L2_QUEUE_SIZE(6)));

		for (i = 0; i < 19; i++)
			IGP_WRITE_MCIND(RS600_MC_PT0_CLIENT0_CNTL + i,
					(RS600_ENABLE_TRANSLATION_MODE_OVERRIDE |
					 RS600_SYSTEM_ACCESS_MODE_IN_SYS |
					 RS600_SYSTEM_APERTURE_UNMAPPED_ACCESS_PASSTHROUGH |
					 RS600_EFFECTIVE_L1_CACHE_SIZE(3) |
					 RS600_ENABLE_FRAGMENT_PROCESSING |
					 RS600_EFFECTIVE_L1_QUEUE_SIZE(3)));

		IGP_WRITE_MCIND(RS600_MC_PT0_CONTEXT0_CNTL, (RS600_ENABLE_PAGE_TABLE |
							     RS600_PAGE_TABLE_TYPE_FLAT));

		/* disable all other contexts */
		for (i = 1; i < 8; i++)
			IGP_WRITE_MCIND(RS600_MC_PT0_CONTEXT0_CNTL + i, 0);

		/* setup the page table aperture */
		IGP_WRITE_MCIND(RS600_MC_PT0_CONTEXT0_FLAT_BASE_ADDR,
				dev_priv->gart_info.bus_addr);
		IGP_WRITE_MCIND(RS600_MC_PT0_CONTEXT0_FLAT_START_ADDR,
				dev_priv->gart_vm_start);
		IGP_WRITE_MCIND(RS600_MC_PT0_CONTEXT0_FLAT_END_ADDR,
				(dev_priv->gart_vm_start + dev_priv->gart_size - 1));
		IGP_WRITE_MCIND(RS600_MC_PT0_CONTEXT0_DEFAULT_READ_ADDR, 0);

		/* setup the system aperture */
		IGP_WRITE_MCIND(RS600_MC_PT0_SYSTEM_APERTURE_LOW_ADDR,
				dev_priv->gart_vm_start);
		IGP_WRITE_MCIND(RS600_MC_PT0_SYSTEM_APERTURE_HIGH_ADDR,
				(dev_priv->gart_vm_start + dev_priv->gart_size - 1));

		/* enable page tables */
		temp = IGP_READ_MCIND(dev_priv, RS600_MC_PT0_CNTL);
		IGP_WRITE_MCIND(RS600_MC_PT0_CNTL, (temp | RS600_ENABLE_PT));

		temp = IGP_READ_MCIND(dev_priv, RS600_MC_CNTL1);
		IGP_WRITE_MCIND(RS600_MC_CNTL1, (temp | RS600_ENABLE_PAGE_TABLES));

		/* invalidate the cache */
		temp = IGP_READ_MCIND(dev_priv, RS600_MC_PT0_CNTL);

		temp &= ~(RS600_INVALIDATE_ALL_L1_TLBS | RS600_INVALIDATE_L2_CACHE);
		IGP_WRITE_MCIND(RS600_MC_PT0_CNTL, temp);
		temp = IGP_READ_MCIND(dev_priv, RS600_MC_PT0_CNTL);

		temp |= RS600_INVALIDATE_ALL_L1_TLBS | RS600_INVALIDATE_L2_CACHE;
		IGP_WRITE_MCIND(RS600_MC_PT0_CNTL, temp);
		temp = IGP_READ_MCIND(dev_priv, RS600_MC_PT0_CNTL);

		temp &= ~(RS600_INVALIDATE_ALL_L1_TLBS | RS600_INVALIDATE_L2_CACHE);
		IGP_WRITE_MCIND(RS600_MC_PT0_CNTL, temp);
		temp = IGP_READ_MCIND(dev_priv, RS600_MC_PT0_CNTL);

	} else {
		IGP_WRITE_MCIND(RS600_MC_PT0_CNTL, 0);
		temp = IGP_READ_MCIND(dev_priv, RS600_MC_CNTL1);
		temp &= ~RS600_ENABLE_PAGE_TABLES;
		IGP_WRITE_MCIND(RS600_MC_CNTL1, temp);
	}
}