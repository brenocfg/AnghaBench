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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  ioc_sem_reg; } ;
struct bfa_ioc {int /*<<< orphan*/  sem_timer; int /*<<< orphan*/  iocpf; TYPE_1__ ioc_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_IOC_HWSEM_TOV ; 
 int /*<<< orphan*/  IOCPF_E_SEMLOCKED ; 
 int /*<<< orphan*/  IOCPF_E_SEM_ERROR ; 
 int /*<<< orphan*/  bfa_fsm_send_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_ioc_hw_sem_get(struct bfa_ioc *ioc)
{
	u32	r32;

	/**
	 * First read to the semaphore register will return 0, subsequent reads
	 * will return 1. Semaphore is released by writing 1 to the register
	 */
	r32 = readl(ioc->ioc_regs.ioc_sem_reg);
	if (r32 == ~0) {
		bfa_fsm_send_event(&ioc->iocpf, IOCPF_E_SEM_ERROR);
		return;
	}
	if (!(r32 & 1)) {
		bfa_fsm_send_event(&ioc->iocpf, IOCPF_E_SEMLOCKED);
		return;
	}

	mod_timer(&ioc->sem_timer, jiffies +
		msecs_to_jiffies(BFA_IOC_HWSEM_TOV));
}