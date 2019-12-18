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
typedef  int /*<<< orphan*/  u32 ;
struct bfa_ioc_s {int dummy; } ;

/* Variables and functions */
 scalar_t__ BFA_STATUS_OK ; 
 int /*<<< orphan*/  BFI_FWBOOT_TYPE_MEMTEST ; 
 int /*<<< orphan*/  BFI_IOC_INITING ; 
 int /*<<< orphan*/  BFI_IOC_MEMTEST ; 
 int /*<<< orphan*/  bfa_ioc_download_fw (struct bfa_ioc_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_lpu_start (struct bfa_ioc_s*) ; 
 int /*<<< orphan*/  bfa_ioc_msgflush (struct bfa_ioc_s*) ; 
 scalar_t__ bfa_ioc_pll_init (struct bfa_ioc_s*) ; 
 int /*<<< orphan*/  bfa_ioc_set_alt_ioc_fwstate (struct bfa_ioc_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_set_cur_ioc_fwstate (struct bfa_ioc_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_stats (struct bfa_ioc_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioc_boots ; 

void
bfa_ioc_boot(struct bfa_ioc_s *ioc, u32 boot_type, u32 boot_env)
{
	bfa_ioc_stats(ioc, ioc_boots);

	if (bfa_ioc_pll_init(ioc) != BFA_STATUS_OK)
		return;

	/*
	 * Initialize IOC state of all functions on a chip reset.
	 */
	if (boot_type == BFI_FWBOOT_TYPE_MEMTEST) {
		bfa_ioc_set_cur_ioc_fwstate(ioc, BFI_IOC_MEMTEST);
		bfa_ioc_set_alt_ioc_fwstate(ioc, BFI_IOC_MEMTEST);
	} else {
		bfa_ioc_set_cur_ioc_fwstate(ioc, BFI_IOC_INITING);
		bfa_ioc_set_alt_ioc_fwstate(ioc, BFI_IOC_INITING);
	}

	bfa_ioc_msgflush(ioc);
	bfa_ioc_download_fw(ioc, boot_type, boot_env);
	bfa_ioc_lpu_start(ioc);
}