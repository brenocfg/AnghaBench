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
struct bfa_ioc {int /*<<< orphan*/  sem_timer; } ;
typedef  enum iocpf_event { ____Placeholder_iocpf_event } iocpf_event ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_IOC_HWSEM_TOV ; 
#define  IOCPF_E_DISABLE 130 
#define  IOCPF_E_SEMLOCKED 129 
#define  IOCPF_E_SEM_ERROR 128 
 int /*<<< orphan*/  bfa_fsm_set_state (struct bfa_iocpf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_hw_sem_get_cancel (struct bfa_ioc*) ; 
 int /*<<< orphan*/  bfa_ioc_pf_hwfailed (struct bfa_ioc*) ; 
 int /*<<< orphan*/  bfa_ioc_sync_complete (struct bfa_ioc*) ; 
 int /*<<< orphan*/  bfa_ioc_sync_join (struct bfa_ioc*) ; 
 int /*<<< orphan*/  bfa_iocpf_sm_disabling_sync ; 
 int /*<<< orphan*/  bfa_iocpf_sm_fail ; 
 int /*<<< orphan*/  bfa_iocpf_sm_hwinit ; 
 int /*<<< orphan*/  bfa_nw_ioc_hw_sem_release (struct bfa_ioc*) ; 
 int /*<<< orphan*/  bfa_sm_fault (int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_iocpf_sm_semwait(struct bfa_iocpf *iocpf, enum iocpf_event event)
{
	struct bfa_ioc *ioc = iocpf->ioc;

	switch (event) {
	case IOCPF_E_SEMLOCKED:
		if (bfa_ioc_sync_complete(ioc)) {
			bfa_ioc_sync_join(ioc);
			bfa_fsm_set_state(iocpf, bfa_iocpf_sm_hwinit);
		} else {
			bfa_nw_ioc_hw_sem_release(ioc);
			mod_timer(&ioc->sem_timer, jiffies +
				msecs_to_jiffies(BFA_IOC_HWSEM_TOV));
		}
		break;

	case IOCPF_E_SEM_ERROR:
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_fail);
		bfa_ioc_pf_hwfailed(ioc);
		break;

	case IOCPF_E_DISABLE:
		bfa_ioc_hw_sem_get_cancel(ioc);
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_disabling_sync);
		break;

	default:
		bfa_sm_fault(event);
	}
}