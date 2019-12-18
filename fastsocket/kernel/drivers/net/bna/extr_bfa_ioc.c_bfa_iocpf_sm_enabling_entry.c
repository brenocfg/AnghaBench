#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bfa_iocpf {TYPE_2__* ioc; } ;
struct TYPE_4__ {int /*<<< orphan*/  bfa; TYPE_1__* cbfn; int /*<<< orphan*/  iocpf_timer; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* reset_cbfn ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_IOC_TOV ; 
 int /*<<< orphan*/  bfa_ioc_send_enable (TYPE_2__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_iocpf_sm_enabling_entry(struct bfa_iocpf *iocpf)
{
	mod_timer(&(iocpf->ioc)->iocpf_timer, jiffies +
		msecs_to_jiffies(BFA_IOC_TOV));
	/**
	 * Enable Interrupts before sending fw IOC ENABLE cmd.
	 */
	iocpf->ioc->cbfn->reset_cbfn(iocpf->ioc->bfa);
	bfa_ioc_send_enable(iocpf->ioc);
}