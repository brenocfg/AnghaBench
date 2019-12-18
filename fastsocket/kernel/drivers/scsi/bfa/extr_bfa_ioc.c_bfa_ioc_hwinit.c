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
struct bfa_ioc_s {int /*<<< orphan*/  iocpf; } ;
typedef  enum bfi_ioc_state { ____Placeholder_bfi_ioc_state } bfi_ioc_state ;
typedef  scalar_t__ bfa_boolean_t ;

/* Variables and functions */
 scalar_t__ BFA_FALSE ; 
 int /*<<< orphan*/  BFI_FWBOOT_ENV_OS ; 
 int /*<<< orphan*/  BFI_FWBOOT_TYPE_NORMAL ; 
 int BFI_IOC_DISABLED ; 
 int BFI_IOC_INITING ; 
 int BFI_IOC_OP ; 
 int BFI_IOC_UNINIT ; 
 int /*<<< orphan*/  IOCPF_E_FWREADY ; 
 int /*<<< orphan*/  bfa_fsm_send_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_boot (struct bfa_ioc_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bfa_ioc_fwver_valid (struct bfa_ioc_s*,int /*<<< orphan*/ ) ; 
 int bfa_ioc_get_cur_ioc_fwstate (struct bfa_ioc_s*) ; 
 int /*<<< orphan*/  bfa_ioc_msgflush (struct bfa_ioc_s*) ; 
 int /*<<< orphan*/  bfa_ioc_poll_fwinit (struct bfa_ioc_s*) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_ioc_s*,int) ; 

__attribute__((used)) static void
bfa_ioc_hwinit(struct bfa_ioc_s *ioc, bfa_boolean_t force)
{
	enum bfi_ioc_state ioc_fwstate;
	bfa_boolean_t fwvalid;
	u32 boot_type;
	u32 boot_env;

	ioc_fwstate = bfa_ioc_get_cur_ioc_fwstate(ioc);

	if (force)
		ioc_fwstate = BFI_IOC_UNINIT;

	bfa_trc(ioc, ioc_fwstate);

	boot_type = BFI_FWBOOT_TYPE_NORMAL;
	boot_env = BFI_FWBOOT_ENV_OS;

	/*
	 * check if firmware is valid
	 */
	fwvalid = (ioc_fwstate == BFI_IOC_UNINIT) ?
		BFA_FALSE : bfa_ioc_fwver_valid(ioc, boot_env);

	if (!fwvalid) {
		bfa_ioc_boot(ioc, boot_type, boot_env);
		bfa_ioc_poll_fwinit(ioc);
		return;
	}

	/*
	 * If hardware initialization is in progress (initialized by other IOC),
	 * just wait for an initialization completion interrupt.
	 */
	if (ioc_fwstate == BFI_IOC_INITING) {
		bfa_ioc_poll_fwinit(ioc);
		return;
	}

	/*
	 * If IOC function is disabled and firmware version is same,
	 * just re-enable IOC.
	 *
	 * If option rom, IOC must not be in operational state. With
	 * convergence, IOC will be in operational state when 2nd driver
	 * is loaded.
	 */
	if (ioc_fwstate == BFI_IOC_DISABLED || ioc_fwstate == BFI_IOC_OP) {

		/*
		 * When using MSI-X any pending firmware ready event should
		 * be flushed. Otherwise MSI-X interrupts are not delivered.
		 */
		bfa_ioc_msgflush(ioc);
		bfa_fsm_send_event(&ioc->iocpf, IOCPF_E_FWREADY);
		return;
	}

	/*
	 * Initialize the h/w for any other states.
	 */
	bfa_ioc_boot(ioc, boot_type, boot_env);
	bfa_ioc_poll_fwinit(ioc);
}