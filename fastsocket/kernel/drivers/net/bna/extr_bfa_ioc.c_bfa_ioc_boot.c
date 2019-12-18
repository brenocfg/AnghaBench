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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  alt_ioc_fwstate; int /*<<< orphan*/  ioc_fwstate; } ;
struct bfa_ioc {TYPE_1__ ioc_regs; } ;
typedef  enum bfi_fwboot_type { ____Placeholder_bfi_fwboot_type } bfi_fwboot_type ;

/* Variables and functions */
 scalar_t__ BFA_STATUS_OK ; 
 int BFI_FWBOOT_TYPE_MEMTEST ; 
 int /*<<< orphan*/  BFI_IOC_INITING ; 
 int /*<<< orphan*/  BFI_IOC_MEMTEST ; 
 int /*<<< orphan*/  bfa_ioc_download_fw (struct bfa_ioc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_lpu_start (struct bfa_ioc*) ; 
 int /*<<< orphan*/  bfa_ioc_msgflush (struct bfa_ioc*) ; 
 scalar_t__ bfa_ioc_pll_init (struct bfa_ioc*) ; 
 int /*<<< orphan*/  bfa_ioc_stats (struct bfa_ioc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioc_boots ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_ioc_boot(struct bfa_ioc *ioc, enum bfi_fwboot_type boot_type,
		u32 boot_env)
{
	bfa_ioc_stats(ioc, ioc_boots);

	if (bfa_ioc_pll_init(ioc) != BFA_STATUS_OK)
		return;

	/**
	 * Initialize IOC state of all functions on a chip reset.
	 */
	if (boot_type == BFI_FWBOOT_TYPE_MEMTEST) {
		writel(BFI_IOC_MEMTEST, ioc->ioc_regs.ioc_fwstate);
		writel(BFI_IOC_MEMTEST, ioc->ioc_regs.alt_ioc_fwstate);
	} else {
		writel(BFI_IOC_INITING, ioc->ioc_regs.ioc_fwstate);
		writel(BFI_IOC_INITING, ioc->ioc_regs.alt_ioc_fwstate);
	}

	bfa_ioc_msgflush(ioc);
	bfa_ioc_download_fw(ioc, boot_type, boot_env);
	bfa_ioc_lpu_start(ioc);
}