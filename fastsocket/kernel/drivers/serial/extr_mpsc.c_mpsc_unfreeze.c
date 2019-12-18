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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  line; } ;
struct mpsc_port_info {TYPE_1__ port; scalar_t__ mpsc_base; int /*<<< orphan*/  MPSC_MPCR_m; scalar_t__ mirror_regs; } ;

/* Variables and functions */
 scalar_t__ MPSC_MPCR ; 
 int /*<<< orphan*/  MPSC_MPCR_FRZ ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mpsc_unfreeze(struct mpsc_port_info *pi)
{
	u32	v;

	v = (pi->mirror_regs) ? pi->MPSC_MPCR_m :
		readl(pi->mpsc_base + MPSC_MPCR);
	v &= ~MPSC_MPCR_FRZ;

	if (pi->mirror_regs)
		pi->MPSC_MPCR_m = v;
	writel(v, pi->mpsc_base + MPSC_MPCR);

	pr_debug("mpsc_unfreeze[%d]: Unfrozen\n", pi->port.line);
}