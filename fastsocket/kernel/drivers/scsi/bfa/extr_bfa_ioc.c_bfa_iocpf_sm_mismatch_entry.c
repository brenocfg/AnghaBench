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
struct bfa_iocpf_s {scalar_t__ fw_mismatch_notified; int /*<<< orphan*/  ioc; } ;

/* Variables and functions */
 scalar_t__ BFA_FALSE ; 
 scalar_t__ BFA_TRUE ; 
 int /*<<< orphan*/  bfa_ioc_pf_fwmismatch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_iocpf_timer_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_iocpf_sm_mismatch_entry(struct bfa_iocpf_s *iocpf)
{
	/*
	 * Call only the first time sm enters fwmismatch state.
	 */
	if (iocpf->fw_mismatch_notified == BFA_FALSE)
		bfa_ioc_pf_fwmismatch(iocpf->ioc);

	iocpf->fw_mismatch_notified = BFA_TRUE;
	bfa_iocpf_timer_start(iocpf->ioc);
}