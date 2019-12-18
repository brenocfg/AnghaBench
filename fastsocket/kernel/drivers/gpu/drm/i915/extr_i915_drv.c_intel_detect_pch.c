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
struct pci_dev {scalar_t__ vendor; unsigned short device; } ;
struct drm_i915_private {unsigned short pch_id; int num_pch_pll; void* pch_type; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int I915_NUM_PLLS ; 
 unsigned short INTEL_PCH_CPT_DEVICE_ID_TYPE ; 
 unsigned short INTEL_PCH_DEVICE_ID_MASK ; 
 unsigned short INTEL_PCH_IBX_DEVICE_ID_TYPE ; 
 unsigned short INTEL_PCH_LPT_DEVICE_ID_TYPE ; 
 unsigned short INTEL_PCH_LPT_LP_DEVICE_ID_TYPE ; 
 unsigned short INTEL_PCH_PPT_DEVICE_ID_TYPE ; 
 int /*<<< orphan*/  IS_GEN5 (struct drm_device*) ; 
 scalar_t__ IS_GEN6 (struct drm_device*) ; 
 int /*<<< orphan*/  IS_HASWELL (struct drm_device*) ; 
 scalar_t__ IS_IVYBRIDGE (struct drm_device*) ; 
 void* PCH_CPT ; 
 void* PCH_IBX ; 
 void* PCH_LPT ; 
 int PCI_CLASS_BRIDGE_ISA ; 
 scalar_t__ PCI_VENDOR_ID_INTEL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct pci_dev* pci_get_class (int,int /*<<< orphan*/ *) ; 

void intel_detect_pch(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct pci_dev *pch;

	/*
	 * The reason to probe ISA bridge instead of Dev31:Fun0 is to
	 * make graphics device passthrough work easy for VMM, that only
	 * need to expose ISA bridge to let driver know the real hardware
	 * underneath. This is a requirement from virtualization team.
	 */
	pch = pci_get_class(PCI_CLASS_BRIDGE_ISA << 8, NULL);
	if (pch) {
		if (pch->vendor == PCI_VENDOR_ID_INTEL) {
			unsigned short id;
			id = pch->device & INTEL_PCH_DEVICE_ID_MASK;
			dev_priv->pch_id = id;

			if (id == INTEL_PCH_IBX_DEVICE_ID_TYPE) {
				dev_priv->pch_type = PCH_IBX;
				dev_priv->num_pch_pll = 2;
				DRM_DEBUG_KMS("Found Ibex Peak PCH\n");
				WARN_ON(!IS_GEN5(dev));
			} else if (id == INTEL_PCH_CPT_DEVICE_ID_TYPE) {
				dev_priv->pch_type = PCH_CPT;
				dev_priv->num_pch_pll = 2;
				DRM_DEBUG_KMS("Found CougarPoint PCH\n");
				WARN_ON(!(IS_GEN6(dev) || IS_IVYBRIDGE(dev)));
			} else if (id == INTEL_PCH_PPT_DEVICE_ID_TYPE) {
				/* PantherPoint is CPT compatible */
				dev_priv->pch_type = PCH_CPT;
				dev_priv->num_pch_pll = 2;
				DRM_DEBUG_KMS("Found PatherPoint PCH\n");
				WARN_ON(!(IS_GEN6(dev) || IS_IVYBRIDGE(dev)));
			} else if (id == INTEL_PCH_LPT_DEVICE_ID_TYPE) {
				dev_priv->pch_type = PCH_LPT;
				dev_priv->num_pch_pll = 0;
				DRM_DEBUG_KMS("Found LynxPoint PCH\n");
				WARN_ON(!IS_HASWELL(dev));
			} else if (id == INTEL_PCH_LPT_LP_DEVICE_ID_TYPE) {
				dev_priv->pch_type = PCH_LPT;
				dev_priv->num_pch_pll = 0;
				DRM_DEBUG_KMS("Found LynxPoint LP PCH\n");
				WARN_ON(!IS_HASWELL(dev));
			}
			BUG_ON(dev_priv->num_pch_pll > I915_NUM_PLLS);
		}
		pci_dev_put(pch);
	}
}