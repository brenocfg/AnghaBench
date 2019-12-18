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
struct TYPE_2__ {int /*<<< orphan*/  line; } ;
struct mpsc_port_info {int MPSC_CHR_2_m; scalar_t__ mpsc_base; scalar_t__ mirror_regs; TYPE_1__ port; } ;

/* Variables and functions */
 scalar_t__ MPSC_CHR_2 ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void mpsc_set_parity(struct mpsc_port_info *pi, u32 p)
{
	u32	v;

	pr_debug("mpsc_set_parity[%d]: parity bits: 0x%x\n", pi->port.line, p);

	v = (pi->mirror_regs) ? pi->MPSC_CHR_2_m :
		readl(pi->mpsc_base + MPSC_CHR_2);

	p &= 0x3;
	v = (v & ~0xc000c) | (p << 18) | (p << 2);

	if (pi->mirror_regs)
		pi->MPSC_CHR_2_m = v;
	writel(v, pi->mpsc_base + MPSC_CHR_2);
}