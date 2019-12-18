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
struct TYPE_2__ {int /*<<< orphan*/  fsm; } ;
struct bfa_ioc {TYPE_1__ iocpf; int /*<<< orphan*/  fsm; } ;
typedef  enum bfa_iocpf_state { ____Placeholder_bfa_iocpf_state } bfa_iocpf_state ;
typedef  enum bfa_ioc_state { ____Placeholder_bfa_ioc_state } bfa_ioc_state ;

/* Variables and functions */
#define  BFA_IOCPF_FAIL 132 
#define  BFA_IOCPF_FWMISMATCH 131 
#define  BFA_IOCPF_HWINIT 130 
#define  BFA_IOCPF_INITFAIL 129 
#define  BFA_IOCPF_SEMWAIT 128 
 int BFA_IOC_ENABLING ; 
 int BFA_IOC_FAIL ; 
 int BFA_IOC_FWMISMATCH ; 
 int BFA_IOC_HWINIT ; 
 int BFA_IOC_INITFAIL ; 
 int BFA_IOC_SEMWAIT ; 
 int bfa_sm_to_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioc_sm_table ; 
 int /*<<< orphan*/  iocpf_sm_table ; 

__attribute__((used)) static enum bfa_ioc_state
bfa_ioc_get_state(struct bfa_ioc *ioc)
{
	enum bfa_iocpf_state iocpf_st;
	enum bfa_ioc_state ioc_st = bfa_sm_to_state(ioc_sm_table, ioc->fsm);

	if (ioc_st == BFA_IOC_ENABLING ||
		ioc_st == BFA_IOC_FAIL || ioc_st == BFA_IOC_INITFAIL) {

		iocpf_st = bfa_sm_to_state(iocpf_sm_table, ioc->iocpf.fsm);

		switch (iocpf_st) {
		case BFA_IOCPF_SEMWAIT:
			ioc_st = BFA_IOC_SEMWAIT;
			break;

		case BFA_IOCPF_HWINIT:
			ioc_st = BFA_IOC_HWINIT;
			break;

		case BFA_IOCPF_FWMISMATCH:
			ioc_st = BFA_IOC_FWMISMATCH;
			break;

		case BFA_IOCPF_FAIL:
			ioc_st = BFA_IOC_FAIL;
			break;

		case BFA_IOCPF_INITFAIL:
			ioc_st = BFA_IOC_INITFAIL;
			break;

		default:
			break;
		}
	}
	return ioc_st;
}