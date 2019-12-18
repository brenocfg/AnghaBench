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
struct TYPE_2__ {int /*<<< orphan*/  ioc_fwstate; } ;
struct bfa_ioc {int /*<<< orphan*/  iocpf; TYPE_1__ ioc_regs; } ;
typedef  enum bfi_ioc_state { ____Placeholder_bfi_ioc_state } bfi_ioc_state ;

/* Variables and functions */
 int /*<<< orphan*/  BFI_FWBOOT_ENV_OS ; 
 int /*<<< orphan*/  BFI_FWBOOT_TYPE_NORMAL ; 
 int BFI_IOC_DISABLED ; 
 int BFI_IOC_INITING ; 
 int BFI_IOC_OP ; 
 int BFI_IOC_UNINIT ; 
 int /*<<< orphan*/  IOCPF_E_FWREADY ; 
 int /*<<< orphan*/  bfa_fsm_send_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_boot (struct bfa_ioc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bfa_ioc_fwver_valid (struct bfa_ioc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_msgflush (struct bfa_ioc*) ; 
 int /*<<< orphan*/  bfa_ioc_poll_fwinit (struct bfa_ioc*) ; 
 int readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_ioc_hwinit(struct bfa_ioc *ioc, bool force)
{
	enum bfi_ioc_state ioc_fwstate;
	bool fwvalid;
	u32 boot_env;

	ioc_fwstate = readl(ioc->ioc_regs.ioc_fwstate);

	if (force)
		ioc_fwstate = BFI_IOC_UNINIT;

	boot_env = BFI_FWBOOT_ENV_OS;

	/**
	 * check if firmware is valid
	 */
	fwvalid = (ioc_fwstate == BFI_IOC_UNINIT) ?
		false : bfa_ioc_fwver_valid(ioc, boot_env);

	if (!fwvalid) {
		bfa_ioc_boot(ioc, BFI_FWBOOT_TYPE_NORMAL, boot_env);
		bfa_ioc_poll_fwinit(ioc);
		return;
	}

	/**
	 * If hardware initialization is in progress (initialized by other IOC),
	 * just wait for an initialization completion interrupt.
	 */
	if (ioc_fwstate == BFI_IOC_INITING) {
		bfa_ioc_poll_fwinit(ioc);
		return;
	}

	/**
	 * If IOC function is disabled and firmware version is same,
	 * just re-enable IOC.
	 */
	if (ioc_fwstate == BFI_IOC_DISABLED || ioc_fwstate == BFI_IOC_OP) {
		/**
		 * When using MSI-X any pending firmware ready event should
		 * be flushed. Otherwise MSI-X interrupts are not delivered.
		 */
		bfa_ioc_msgflush(ioc);
		bfa_fsm_send_event(&ioc->iocpf, IOCPF_E_FWREADY);
		return;
	}

	/**
	 * Initialize the h/w for any other states.
	 */
	bfa_ioc_boot(ioc, BFI_FWBOOT_TYPE_NORMAL, boot_env);
	bfa_ioc_poll_fwinit(ioc);
}