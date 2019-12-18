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
typedef  int u8 ;
typedef  int u32 ;
struct pci_dev {int dummy; } ;
struct TYPE_5__ {TYPE_1__* gtt; } ;
struct drm_i915_private {TYPE_2__ mm; struct pci_dev* bridge_dev; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
struct TYPE_6__ {int gen; } ;
struct TYPE_4__ {scalar_t__ stolen_size; } ;

/* Variables and functions */
 TYPE_3__* INTEL_INFO (struct drm_device*) ; 
 scalar_t__ IS_G33 (struct drm_device*) ; 
 scalar_t__ IS_GEN3 (struct drm_device*) ; 
 int PAGE_SHIFT ; 
 int max_low_pfn_mapped ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,int*) ; 

__attribute__((used)) static unsigned long i915_stolen_to_physical(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct pci_dev *pdev = dev_priv->bridge_dev;
	u32 base;

	/* On the machines I have tested the Graphics Base of Stolen Memory
	 * is unreliable, so on those compute the base by subtracting the
	 * stolen memory from the Top of Low Usable DRAM which is where the
	 * BIOS places the graphics stolen memory.
	 *
	 * On gen2, the layout is slightly different with the Graphics Segment
	 * immediately following Top of Memory (or Top of Usable DRAM). Note
	 * it appears that TOUD is only reported by 865g, so we just use the
	 * top of memory as determined by the e820 probe.
	 *
	 * XXX gen2 requires an unavailable symbol and 945gm fails with
	 * its value of TOLUD.
	 */
	base = 0;
	if (INTEL_INFO(dev)->gen >= 6) {
		/* Read Base Data of Stolen Memory Register (BDSM) directly.
		 * Note that there is also a MCHBAR miror at 0x1080c0 or
		 * we could use device 2:0x5c instead.
		*/
		pci_read_config_dword(pdev, 0xB0, &base);
		base &= ~4095; /* lower bits used for locking register */
	} else if (INTEL_INFO(dev)->gen > 3 || IS_G33(dev)) {
		/* Read Graphics Base of Stolen Memory directly */
		pci_read_config_dword(pdev, 0xA4, &base);
#if 0
	} else if (IS_GEN3(dev)) {
		u8 val;
		/* Stolen is immediately below Top of Low Usable DRAM */
		pci_read_config_byte(pdev, 0x9c, &val);
		base = val >> 3 << 27;
		base -= dev_priv->mm.gtt->stolen_size;
	} else {
		/* Stolen is immediately above Top of Memory */
		base = max_low_pfn_mapped << PAGE_SHIFT;
#endif
	}

	return base;
}