#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct bfa_iocpf_s {TYPE_2__* ioc; } ;
struct TYPE_5__ {int /*<<< orphan*/  bfa; TYPE_1__* cbfn; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* reset_cbfn ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_ioc_send_enable (TYPE_2__*) ; 
 int /*<<< orphan*/  bfa_iocpf_timer_start (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_iocpf_sm_enabling_entry(struct bfa_iocpf_s *iocpf)
{
	bfa_iocpf_timer_start(iocpf->ioc);
	/*
	 * Enable Interrupts before sending fw IOC ENABLE cmd.
	 */
	iocpf->ioc->cbfn->reset_cbfn(iocpf->ioc->bfa);
	bfa_ioc_send_enable(iocpf->ioc);
}