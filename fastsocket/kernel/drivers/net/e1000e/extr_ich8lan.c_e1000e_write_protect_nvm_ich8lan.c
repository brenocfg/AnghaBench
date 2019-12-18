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
struct TYPE_5__ {int flockdn; } ;
union ich8_hws_flash_status {void* regval; TYPE_2__ hsf_status; } ;
struct TYPE_4__ {int base; int limit; int wpe; } ;
union ich8_flash_protected_range {void* regval; TYPE_1__ range; } ;
typedef  int u32 ;
struct TYPE_6__ {int /*<<< orphan*/  (* release ) (struct e1000_hw*) ;int /*<<< orphan*/  (* acquire ) (struct e1000_hw*) ;} ;
struct e1000_nvm_info {TYPE_3__ ops; } ;
struct e1000_hw {struct e1000_nvm_info nvm; } ;

/* Variables and functions */
 int FLASH_GFPREG_BASE_MASK ; 
 int /*<<< orphan*/  ICH_FLASH_GFPREG ; 
 int /*<<< orphan*/  ICH_FLASH_HSFSTS ; 
 int /*<<< orphan*/  ICH_FLASH_PR0 ; 
 void* er16flash (int /*<<< orphan*/ ) ; 
 void* er32flash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32flash (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  stub1 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub2 (struct e1000_hw*) ; 

void e1000e_write_protect_nvm_ich8lan(struct e1000_hw *hw)
{
	struct e1000_nvm_info *nvm = &hw->nvm;
	union ich8_flash_protected_range pr0;
	union ich8_hws_flash_status hsfsts;
	u32 gfpreg;

	nvm->ops.acquire(hw);

	gfpreg = er32flash(ICH_FLASH_GFPREG);

	/* Write-protect GbE Sector of NVM */
	pr0.regval = er32flash(ICH_FLASH_PR0);
	pr0.range.base = gfpreg & FLASH_GFPREG_BASE_MASK;
	pr0.range.limit = ((gfpreg >> 16) & FLASH_GFPREG_BASE_MASK);
	pr0.range.wpe = true;
	ew32flash(ICH_FLASH_PR0, pr0.regval);

	/* Lock down a subset of GbE Flash Control Registers, e.g.
	 * PR0 to prevent the write-protection from being lifted.
	 * Once FLOCKDN is set, the registers protected by it cannot
	 * be written until FLOCKDN is cleared by a hardware reset.
	 */
	hsfsts.regval = er16flash(ICH_FLASH_HSFSTS);
	hsfsts.hsf_status.flockdn = true;
	ew32flash(ICH_FLASH_HSFSTS, hsfsts.regval);

	nvm->ops.release(hw);
}