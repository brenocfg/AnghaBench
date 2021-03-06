#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {int /*<<< orphan*/  core; } ;
struct TYPE_3__ {scalar_t__ id; } ;
struct bcma_bus {int /*<<< orphan*/  sprom; TYPE_2__ drv_cc; TYPE_1__ chipinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_CC_SPROM ; 
 scalar_t__ BCMA_CHIP_ID_BCM4331 ; 
 scalar_t__ BCMA_CHIP_ID_BCM43431 ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SSB_SPROMSIZE_WORDS_R4 ; 
 int /*<<< orphan*/  bcma_chipco_bcm4331_ext_pa_lines_ctl (TYPE_2__*,int) ; 
 int /*<<< orphan*/  bcma_debug (struct bcma_bus*,char*,int /*<<< orphan*/ ) ; 
 int bcma_fill_sprom_with_fallback (struct bcma_bus*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bcma_sprom_ext_available (struct bcma_bus*) ; 
 int /*<<< orphan*/  bcma_sprom_extract_r8 (struct bcma_bus*,int /*<<< orphan*/ *) ; 
 int bcma_sprom_onchip_available (struct bcma_bus*) ; 
 int /*<<< orphan*/  bcma_sprom_onchip_offset (struct bcma_bus*) ; 
 int /*<<< orphan*/  bcma_sprom_read (struct bcma_bus*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bcma_sprom_valid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bcma_warn (struct bcma_bus*,char*) ; 
 int /*<<< orphan*/ * kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

int bcma_sprom_get(struct bcma_bus *bus)
{
	u16 offset = BCMA_CC_SPROM;
	u16 *sprom;
	int err = 0;

	if (!bus->drv_cc.core)
		return -EOPNOTSUPP;

	if (!bcma_sprom_ext_available(bus)) {
		bool sprom_onchip;

		/*
		 * External SPROM takes precedence so check
		 * on-chip OTP only when no external SPROM
		 * is present.
		 */
		sprom_onchip = bcma_sprom_onchip_available(bus);
		if (sprom_onchip) {
			/* determine offset */
			offset = bcma_sprom_onchip_offset(bus);
		}
		if (!offset || !sprom_onchip) {
			/*
			 * Maybe there is no SPROM on the device?
			 * Now we ask the arch code if there is some sprom
			 * available for this device in some other storage.
			 */
			err = bcma_fill_sprom_with_fallback(bus, &bus->sprom);
			return err;
		}
	}

	sprom = kcalloc(SSB_SPROMSIZE_WORDS_R4, sizeof(u16),
			GFP_KERNEL);
	if (!sprom)
		return -ENOMEM;

	if (bus->chipinfo.id == BCMA_CHIP_ID_BCM4331 ||
	    bus->chipinfo.id == BCMA_CHIP_ID_BCM43431)
		bcma_chipco_bcm4331_ext_pa_lines_ctl(&bus->drv_cc, false);

	bcma_debug(bus, "SPROM offset 0x%x\n", offset);
	bcma_sprom_read(bus, offset, sprom);

	if (bus->chipinfo.id == BCMA_CHIP_ID_BCM4331 ||
	    bus->chipinfo.id == BCMA_CHIP_ID_BCM43431)
		bcma_chipco_bcm4331_ext_pa_lines_ctl(&bus->drv_cc, true);

	err = bcma_sprom_valid(sprom);
	if (err) {
		bcma_warn(bus, "invalid sprom read from the PCIe card, try to use fallback sprom\n");
		err = bcma_fill_sprom_with_fallback(bus, &bus->sprom);
		goto out;
	}

	bcma_sprom_extract_r8(bus, sprom);

out:
	kfree(sprom);
	return err;
}