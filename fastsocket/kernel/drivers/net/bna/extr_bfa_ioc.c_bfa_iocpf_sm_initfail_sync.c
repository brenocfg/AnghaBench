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
struct bfa_iocpf {struct bfa_ioc* ioc; } ;
struct TYPE_2__ {int /*<<< orphan*/  ioc_fwstate; } ;
struct bfa_ioc {TYPE_1__ ioc_regs; } ;
typedef  enum iocpf_event { ____Placeholder_iocpf_event } iocpf_event ;

/* Variables and functions */
 int /*<<< orphan*/  BFI_IOC_FAIL ; 
#define  IOCPF_E_DISABLE 132 
#define  IOCPF_E_FAIL 131 
#define  IOCPF_E_SEMLOCKED 130 
#define  IOCPF_E_SEM_ERROR 129 
#define  IOCPF_E_STOP 128 
 int /*<<< orphan*/  bfa_fsm_set_state (struct bfa_iocpf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_firmware_unlock (struct bfa_ioc*) ; 
 int /*<<< orphan*/  bfa_ioc_hw_sem_get_cancel (struct bfa_ioc*) ; 
 int /*<<< orphan*/  bfa_ioc_notify_fail (struct bfa_ioc*) ; 
 int /*<<< orphan*/  bfa_ioc_pf_hwfailed (struct bfa_ioc*) ; 
 int /*<<< orphan*/  bfa_ioc_sync_leave (struct bfa_ioc*) ; 
 int /*<<< orphan*/  bfa_iocpf_sm_disabling_sync ; 
 int /*<<< orphan*/  bfa_iocpf_sm_fail ; 
 int /*<<< orphan*/  bfa_iocpf_sm_initfail ; 
 int /*<<< orphan*/  bfa_iocpf_sm_reset ; 
 int /*<<< orphan*/  bfa_nw_ioc_hw_sem_release (struct bfa_ioc*) ; 
 int /*<<< orphan*/  bfa_sm_fault (int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_iocpf_sm_initfail_sync(struct bfa_iocpf *iocpf, enum iocpf_event event)
{
	struct bfa_ioc *ioc = iocpf->ioc;

	switch (event) {
	case IOCPF_E_SEMLOCKED:
		bfa_ioc_notify_fail(ioc);
		bfa_ioc_sync_leave(ioc);
		writel(BFI_IOC_FAIL, ioc->ioc_regs.ioc_fwstate);
		bfa_nw_ioc_hw_sem_release(ioc);
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_initfail);
		break;

	case IOCPF_E_SEM_ERROR:
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_fail);
		bfa_ioc_pf_hwfailed(ioc);
		break;

	case IOCPF_E_DISABLE:
		bfa_ioc_hw_sem_get_cancel(ioc);
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_disabling_sync);
		break;

	case IOCPF_E_STOP:
		bfa_ioc_hw_sem_get_cancel(ioc);
		bfa_ioc_firmware_unlock(ioc);
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_reset);
		break;

	case IOCPF_E_FAIL:
		break;

	default:
		bfa_sm_fault(event);
	}
}