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
struct TYPE_5__ {char* name; scalar_t__ start; int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {TYPE_1__* pcidev; int /*<<< orphan*/  i9xx_flush_page; TYPE_2__ ifp_resource; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int INTEL_GTT_GEN ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_G33 ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  intel_i915_setup_chipset_flush () ; 
 int /*<<< orphan*/  intel_i965_g33_setup_chipset_flush () ; 
 TYPE_3__ intel_private ; 
 int /*<<< orphan*/  ioremap_nocache (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_i9xx_setup_flush(void)
{
	/* return if already configured */
	if (intel_private.ifp_resource.start)
		return;

	if (INTEL_GTT_GEN == 6)
		return;

	/* setup a resource for this object */
	intel_private.ifp_resource.name = "Intel Flush Page";
	intel_private.ifp_resource.flags = IORESOURCE_MEM;

	/* Setup chipset flush for 915 */
	if (IS_G33 || INTEL_GTT_GEN >= 4) {
		intel_i965_g33_setup_chipset_flush();
	} else {
		intel_i915_setup_chipset_flush();
	}

	if (intel_private.ifp_resource.start)
		intel_private.i9xx_flush_page = ioremap_nocache(intel_private.ifp_resource.start, PAGE_SIZE);
	if (!intel_private.i9xx_flush_page)
		dev_err(&intel_private.pcidev->dev,
			"can't ioremap flush page - no chipset flushing\n");
}