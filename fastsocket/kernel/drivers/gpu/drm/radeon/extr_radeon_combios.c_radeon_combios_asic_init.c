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
typedef  scalar_t__ uint16_t ;
struct radeon_device {int flags; scalar_t__ family; TYPE_1__* pdev; int /*<<< orphan*/ * bios; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct TYPE_2__ {int subsystem_vendor; int subsystem_device; } ;

/* Variables and functions */
 scalar_t__ CHIP_RS480 ; 
 int /*<<< orphan*/  COMBIOS_ASIC_INIT_1_TABLE ; 
 int /*<<< orphan*/  COMBIOS_ASIC_INIT_2_TABLE ; 
 int /*<<< orphan*/  COMBIOS_ASIC_INIT_3_TABLE ; 
 int /*<<< orphan*/  COMBIOS_ASIC_INIT_4_TABLE ; 
 int /*<<< orphan*/  COMBIOS_DYN_CLK_1_TABLE ; 
 int /*<<< orphan*/  COMBIOS_PLL_INIT_TABLE ; 
 int /*<<< orphan*/  COMBIOS_RAM_RESET_TABLE ; 
 int RADEON_IS_IGP ; 
 scalar_t__ combios_get_table_offset (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  combios_parse_mmio_table (struct drm_device*,scalar_t__) ; 
 int /*<<< orphan*/  combios_parse_pll_table (struct drm_device*,scalar_t__) ; 
 int /*<<< orphan*/  combios_parse_ram_reset_table (struct drm_device*,scalar_t__) ; 
 int /*<<< orphan*/  combios_write_ram_size (struct drm_device*) ; 

void radeon_combios_asic_init(struct drm_device *dev)
{
	struct radeon_device *rdev = dev->dev_private;
	uint16_t table;

	/* port hardcoded mac stuff from radeonfb */
	if (rdev->bios == NULL)
		return;

	/* ASIC INIT 1 */
	table = combios_get_table_offset(dev, COMBIOS_ASIC_INIT_1_TABLE);
	if (table)
		combios_parse_mmio_table(dev, table);

	/* PLL INIT */
	table = combios_get_table_offset(dev, COMBIOS_PLL_INIT_TABLE);
	if (table)
		combios_parse_pll_table(dev, table);

	/* ASIC INIT 2 */
	table = combios_get_table_offset(dev, COMBIOS_ASIC_INIT_2_TABLE);
	if (table)
		combios_parse_mmio_table(dev, table);

	if (!(rdev->flags & RADEON_IS_IGP)) {
		/* ASIC INIT 4 */
		table =
		    combios_get_table_offset(dev, COMBIOS_ASIC_INIT_4_TABLE);
		if (table)
			combios_parse_mmio_table(dev, table);

		/* RAM RESET */
		table = combios_get_table_offset(dev, COMBIOS_RAM_RESET_TABLE);
		if (table)
			combios_parse_ram_reset_table(dev, table);

		/* ASIC INIT 3 */
		table =
		    combios_get_table_offset(dev, COMBIOS_ASIC_INIT_3_TABLE);
		if (table)
			combios_parse_mmio_table(dev, table);

		/* write CONFIG_MEMSIZE */
		combios_write_ram_size(dev);
	}

	/* quirk for rs4xx HP nx6125 laptop to make it resume
	 * - it hangs on resume inside the dynclk 1 table.
	 */
	if (rdev->family == CHIP_RS480 &&
	    rdev->pdev->subsystem_vendor == 0x103c &&
	    rdev->pdev->subsystem_device == 0x308b)
		return;

	/* quirk for rs4xx HP dv5000 laptop to make it resume
	 * - it hangs on resume inside the dynclk 1 table.
	 */
	if (rdev->family == CHIP_RS480 &&
	    rdev->pdev->subsystem_vendor == 0x103c &&
	    rdev->pdev->subsystem_device == 0x30a4)
		return;

	/* quirk for rs4xx Compaq Presario V5245EU laptop to make it resume
	 * - it hangs on resume inside the dynclk 1 table.
	 */
	if (rdev->family == CHIP_RS480 &&
	    rdev->pdev->subsystem_vendor == 0x103c &&
	    rdev->pdev->subsystem_device == 0x30ae)
		return;

	/* DYN CLK 1 */
	table = combios_get_table_offset(dev, COMBIOS_DYN_CLK_1_TABLE);
	if (table)
		combios_parse_pll_table(dev, table);

}