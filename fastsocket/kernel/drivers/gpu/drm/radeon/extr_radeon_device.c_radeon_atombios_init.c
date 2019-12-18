#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* atom_context; struct card_info* atom_card_info; } ;
struct radeon_device {TYPE_1__ mode_info; int /*<<< orphan*/  ddev; int /*<<< orphan*/  bios; scalar_t__ rio_mem; } ;
struct card_info {int /*<<< orphan*/  pll_write; int /*<<< orphan*/  pll_read; int /*<<< orphan*/  mc_write; int /*<<< orphan*/  mc_read; void* ioreg_write; void* ioreg_read; void* reg_write; void* reg_read; int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atom_allocate_fb_scratch (TYPE_2__*) ; 
 TYPE_2__* atom_parse (struct card_info*,int /*<<< orphan*/ ) ; 
 void* cail_ioreg_read ; 
 void* cail_ioreg_write ; 
 int /*<<< orphan*/  cail_mc_read ; 
 int /*<<< orphan*/  cail_mc_write ; 
 int /*<<< orphan*/  cail_pll_read ; 
 int /*<<< orphan*/  cail_pll_write ; 
 void* cail_reg_read ; 
 void* cail_reg_write ; 
 struct card_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_atom_initialize_bios_scratch_regs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_atombios_fini (struct radeon_device*) ; 

int radeon_atombios_init(struct radeon_device *rdev)
{
	struct card_info *atom_card_info =
	    kzalloc(sizeof(struct card_info), GFP_KERNEL);

	if (!atom_card_info)
		return -ENOMEM;

	rdev->mode_info.atom_card_info = atom_card_info;
	atom_card_info->dev = rdev->ddev;
	atom_card_info->reg_read = cail_reg_read;
	atom_card_info->reg_write = cail_reg_write;
	/* needed for iio ops */
	if (rdev->rio_mem) {
		atom_card_info->ioreg_read = cail_ioreg_read;
		atom_card_info->ioreg_write = cail_ioreg_write;
	} else {
		DRM_ERROR("Unable to find PCI I/O BAR; using MMIO for ATOM IIO\n");
		atom_card_info->ioreg_read = cail_reg_read;
		atom_card_info->ioreg_write = cail_reg_write;
	}
	atom_card_info->mc_read = cail_mc_read;
	atom_card_info->mc_write = cail_mc_write;
	atom_card_info->pll_read = cail_pll_read;
	atom_card_info->pll_write = cail_pll_write;

	rdev->mode_info.atom_context = atom_parse(atom_card_info, rdev->bios);
	if (!rdev->mode_info.atom_context) {
		radeon_atombios_fini(rdev);
		return -ENOMEM;
	}

	mutex_init(&rdev->mode_info.atom_context->mutex);
	radeon_atom_initialize_bios_scratch_regs(rdev->ddev);
	atom_allocate_fb_scratch(rdev->mode_info.atom_context);
	return 0;
}