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
typedef  int /*<<< orphan*/  u8 ;
struct bfa_iocpf {int dummy; } ;
struct bfa_ioc {int port_mode; int port_mode_cfg; int /*<<< orphan*/  ad_cap_bm; struct bfa_iocpf iocpf; } ;
typedef  enum bfa_mode { ____Placeholder_bfa_mode } bfa_mode ;

/* Variables and functions */
 int /*<<< orphan*/  IOCPF_E_FWRSP_ENABLE ; 
 int /*<<< orphan*/  bfa_fsm_send_event (struct bfa_iocpf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_ioc_enable_reply(struct bfa_ioc *ioc, enum bfa_mode port_mode,
			u8 cap_bm)
{
	struct bfa_iocpf *iocpf = &ioc->iocpf;

	ioc->port_mode = ioc->port_mode_cfg = port_mode;
	ioc->ad_cap_bm = cap_bm;
	bfa_fsm_send_event(iocpf, IOCPF_E_FWRSP_ENABLE);
}