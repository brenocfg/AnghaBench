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
struct pci_device_id {scalar_t__ driver_data; } ;
struct pci_dev {int /*<<< orphan*/  devfn; } ;
struct intel_device_info {int gen; scalar_t__ is_valleyview; } ;
struct TYPE_3__ {int driver_features; } ;

/* Variables and functions */
 int DRIVER_REQUIRE_AGP ; 
 int DRIVER_USE_AGP ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ENODEV ; 
 scalar_t__ PCI_FUNC (int /*<<< orphan*/ ) ; 
 TYPE_1__ driver ; 
 int drm_get_pci_dev (struct pci_dev*,struct pci_device_id const*,TYPE_1__*) ; 
 int /*<<< orphan*/  i915_preliminary_hw_support ; 
 int /*<<< orphan*/  intel_agp_enabled ; 

__attribute__((used)) static int i915_pci_probe(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	struct intel_device_info *intel_info =
		(struct intel_device_info *) ent->driver_data;

	if (intel_info->is_valleyview)
		if(!i915_preliminary_hw_support) {
			DRM_ERROR("Preliminary hardware support disabled\n");
			return -ENODEV;
		}

	/* Only bind to function 0 of the device. Early generations
	 * used function 1 as a placeholder for multi-head. This causes
	 * us confusion instead, especially on the systems where both
	 * functions have the same PCI-ID!
	 */
	if (PCI_FUNC(pdev->devfn))
		return -ENODEV;

	/* We've managed to ship a kms-enabled ddx that shipped with an XvMC
	 * implementation for gen3 (and only gen3) that used legacy drm maps
	 * (gasp!) to share buffers between X and the client. Hence we need to
	 * keep around the fake agp stuff for gen3, even when kms is enabled. */
	if (intel_info->gen != 3) {
		driver.driver_features &=
			~(DRIVER_USE_AGP | DRIVER_REQUIRE_AGP);
	} else if (!intel_agp_enabled) {
		DRM_ERROR("drm/i915 can't work without intel_agp module!\n");
		return -ENODEV;
	}

	return drm_get_pci_dev(pdev, ent, &driver);
}