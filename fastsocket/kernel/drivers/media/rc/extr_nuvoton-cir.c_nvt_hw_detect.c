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
typedef  int u8 ;
struct nvt_dev {int chip_major; int chip_minor; int /*<<< orphan*/  nvt_lock; int /*<<< orphan*/  cr_efdr; int /*<<< orphan*/  cr_efir; } ;

/* Variables and functions */
 int CHIP_ID_HIGH ; 
 int CHIP_ID_LOW ; 
 int CHIP_ID_LOW2 ; 
 int /*<<< orphan*/  CR_CHIP_ID_HI ; 
 int /*<<< orphan*/  CR_CHIP_ID_LO ; 
 int /*<<< orphan*/  CR_EFDR2 ; 
 int /*<<< orphan*/  CR_EFIR2 ; 
 int ENODEV ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  chip_id ; 
 int nvt_cr_read (struct nvt_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvt_dbg (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  nvt_efm_disable (struct nvt_dev*) ; 
 int /*<<< orphan*/  nvt_efm_enable (struct nvt_dev*) ; 
 int /*<<< orphan*/  nvt_pr (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int nvt_hw_detect(struct nvt_dev *nvt)
{
	unsigned long flags;
	u8 chip_major, chip_minor;
	int ret = 0;

	nvt_efm_enable(nvt);

	/* Check if we're wired for the alternate EFER setup */
	chip_major = nvt_cr_read(nvt, CR_CHIP_ID_HI);
	if (chip_major == 0xff) {
		nvt->cr_efir = CR_EFIR2;
		nvt->cr_efdr = CR_EFDR2;
		nvt_efm_enable(nvt);
		chip_major = nvt_cr_read(nvt, CR_CHIP_ID_HI);
	}

	chip_minor = nvt_cr_read(nvt, CR_CHIP_ID_LO);
	nvt_dbg("%s: chip id: 0x%02x 0x%02x", chip_id, chip_major, chip_minor);

	if (chip_major != CHIP_ID_HIGH ||
	    (chip_minor != CHIP_ID_LOW && chip_minor != CHIP_ID_LOW2)) {
		nvt_pr(KERN_ERR, "%s: unsupported chip, id: 0x%02x 0x%02x",
		       chip_id, chip_major, chip_minor);
		ret = -ENODEV;
	}

	nvt_efm_disable(nvt);

	spin_lock_irqsave(&nvt->nvt_lock, flags);
	nvt->chip_major = chip_major;
	nvt->chip_minor = chip_minor;
	spin_unlock_irqrestore(&nvt->nvt_lock, flags);

	return ret;
}