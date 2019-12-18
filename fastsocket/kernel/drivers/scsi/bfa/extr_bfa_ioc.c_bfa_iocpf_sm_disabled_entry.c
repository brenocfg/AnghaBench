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
struct bfa_iocpf_s {int /*<<< orphan*/  ioc; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOC_E_DISABLED ; 
 int /*<<< orphan*/  bfa_fsm_send_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_mbox_flush (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_iocpf_sm_disabled_entry(struct bfa_iocpf_s *iocpf)
{
	bfa_ioc_mbox_flush(iocpf->ioc);
	bfa_fsm_send_event(iocpf->ioc, IOC_E_DISABLED);	
}