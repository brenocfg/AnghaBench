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
struct TYPE_2__ {int /*<<< orphan*/  alt_ioc_fwstate; } ;
struct bfa_ioc_s {TYPE_1__ ioc_regs; } ;
typedef  enum bfi_ioc_state { ____Placeholder_bfi_ioc_state } bfi_ioc_state ;

/* Variables and functions */
 int BFA_IOC_CB_JOIN_MASK ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_ioc_cb_set_alt_ioc_fwstate(struct bfa_ioc_s *ioc,
			enum bfi_ioc_state fwstate)
{
	u32 r32 = readl(ioc->ioc_regs.alt_ioc_fwstate);

	writel((fwstate | (r32 & BFA_IOC_CB_JOIN_MASK)),
				ioc->ioc_regs.alt_ioc_fwstate);
}