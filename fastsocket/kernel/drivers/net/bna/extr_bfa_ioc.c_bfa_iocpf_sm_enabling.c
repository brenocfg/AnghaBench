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
struct bfa_iocpf {struct bfa_ioc* ioc; } ;
struct bfa_ioc {int /*<<< orphan*/  iocpf_timer; } ;
typedef  enum iocpf_event { ____Placeholder_iocpf_event } iocpf_event ;

/* Variables and functions */
#define  IOCPF_E_DISABLE 131 
#define  IOCPF_E_FWRSP_ENABLE 130 
#define  IOCPF_E_INITFAIL 129 
#define  IOCPF_E_TIMEOUT 128 
 int /*<<< orphan*/  bfa_fsm_set_state (struct bfa_iocpf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_pf_failed (struct bfa_ioc*) ; 
 int /*<<< orphan*/  bfa_iocpf_sm_disabling ; 
 int /*<<< orphan*/  bfa_iocpf_sm_initfail_sync ; 
 int /*<<< orphan*/  bfa_iocpf_sm_ready ; 
 int /*<<< orphan*/  bfa_nw_ioc_hw_sem_release (struct bfa_ioc*) ; 
 int /*<<< orphan*/  bfa_sm_fault (int) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bfa_iocpf_sm_enabling(struct bfa_iocpf *iocpf, enum iocpf_event event)
{
	struct bfa_ioc *ioc = iocpf->ioc;

	switch (event) {
	case IOCPF_E_FWRSP_ENABLE:
		del_timer(&ioc->iocpf_timer);
		bfa_nw_ioc_hw_sem_release(ioc);
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_ready);
		break;

	case IOCPF_E_INITFAIL:
		del_timer(&ioc->iocpf_timer);
		/*
		 * !!! fall through !!!
		 */
	case IOCPF_E_TIMEOUT:
		bfa_nw_ioc_hw_sem_release(ioc);
		if (event == IOCPF_E_TIMEOUT)
			bfa_ioc_pf_failed(ioc);
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_initfail_sync);
		break;

	case IOCPF_E_DISABLE:
		del_timer(&ioc->iocpf_timer);
		bfa_nw_ioc_hw_sem_release(ioc);
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_disabling);
		break;

	default:
		bfa_sm_fault(event);
	}
}