#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {TYPE_3__* resource; } ;
struct TYPE_6__ {scalar_t__ start; scalar_t__ mappable_end; int /*<<< orphan*/  mappable_base; } ;
struct drm_i915_private {TYPE_2__ gtt; TYPE_4__* dev; } ;
struct apertures_struct {TYPE_1__* ranges; } ;
struct TYPE_8__ {struct pci_dev* pdev; } ;
struct TYPE_7__ {int flags; } ;
struct TYPE_5__ {scalar_t__ size; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int IORESOURCE_ROM_SHADOW ; 
 size_t PCI_ROM_RESOURCE ; 
 struct apertures_struct* alloc_apertures (int) ; 
 int /*<<< orphan*/  kfree (struct apertures_struct*) ; 
 int /*<<< orphan*/  remove_conflicting_framebuffers (struct apertures_struct*,char*,int) ; 

__attribute__((used)) static void i915_kick_out_firmware_fb(struct drm_i915_private *dev_priv)
{
	struct apertures_struct *ap;
	struct pci_dev *pdev = dev_priv->dev->pdev;
	bool primary;

	ap = alloc_apertures(1);
	if (!ap)
		return;

	ap->ranges[0].base = dev_priv->gtt.mappable_base;
	ap->ranges[0].size = dev_priv->gtt.mappable_end - dev_priv->gtt.start;

	primary =
		pdev->resource[PCI_ROM_RESOURCE].flags & IORESOURCE_ROM_SHADOW;

	remove_conflicting_framebuffers(ap, "inteldrmfb", primary);

	kfree(ap);
}