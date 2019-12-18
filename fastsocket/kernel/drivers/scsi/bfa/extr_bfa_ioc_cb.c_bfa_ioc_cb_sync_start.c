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
struct TYPE_2__ {int /*<<< orphan*/  alt_ioc_fwstate; int /*<<< orphan*/  ioc_fwstate; } ;
struct bfa_ioc_s {TYPE_1__ ioc_regs; } ;
typedef  int /*<<< orphan*/  bfa_boolean_t ;

/* Variables and functions */
 int BFA_IOC_CB_JOIN_MASK ; 
 int /*<<< orphan*/  BFA_TRUE ; 
 int /*<<< orphan*/  BFI_IOC_UNINIT ; 
 int /*<<< orphan*/  bfa_ioc_cb_sync_complete (struct bfa_ioc_s*) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfa_boolean_t
bfa_ioc_cb_sync_start(struct bfa_ioc_s *ioc)
{
	u32 ioc_fwstate = readl(ioc->ioc_regs.ioc_fwstate);

	/**
	 * Driver load time.  If the join bit is set,
	 * it is due to an unclean exit by the driver for this
	 * PCI fn in the previous incarnation. Whoever comes here first
	 * should clean it up, no matter which PCI fn.
	 */
	if (ioc_fwstate & BFA_IOC_CB_JOIN_MASK) {
		writel(BFI_IOC_UNINIT, ioc->ioc_regs.ioc_fwstate);
		writel(BFI_IOC_UNINIT, ioc->ioc_regs.alt_ioc_fwstate);
		return BFA_TRUE;
	}

	return bfa_ioc_cb_sync_complete(ioc);
}