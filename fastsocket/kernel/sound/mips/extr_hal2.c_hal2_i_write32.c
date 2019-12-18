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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct snd_hal2 {struct hal2_ctl_regs* ctl_regs; } ;
struct hal2_ctl_regs {int /*<<< orphan*/  iar; int /*<<< orphan*/  idr3; int /*<<< orphan*/  idr2; int /*<<< orphan*/  idr1; int /*<<< orphan*/  idr0; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2_INDIRECT_WAIT (struct hal2_ctl_regs*) ; 
 int H2_WRITE_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hal2_write (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hal2_i_write32(struct snd_hal2 *hal2, u16 addr, u32 val)
{
	struct hal2_ctl_regs *regs = hal2->ctl_regs;

	hal2_write(val & 0xffff, &regs->idr0);
	hal2_write(val >> 16, &regs->idr1);
	hal2_write(0, &regs->idr2);
	hal2_write(0, &regs->idr3);
	hal2_write(H2_WRITE_ADDR(addr), &regs->iar);
	H2_INDIRECT_WAIT(regs);
}