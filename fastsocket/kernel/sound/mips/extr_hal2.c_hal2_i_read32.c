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
struct hal2_ctl_regs {int /*<<< orphan*/  idr0; int /*<<< orphan*/  iar; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2_INDIRECT_WAIT (struct hal2_ctl_regs*) ; 
 int H2_READ_ADDR (int /*<<< orphan*/ ) ; 
 int hal2_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hal2_write (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 hal2_i_read32(struct snd_hal2 *hal2, u16 addr)
{
	u32 ret;
	struct hal2_ctl_regs *regs = hal2->ctl_regs;

	hal2_write(H2_READ_ADDR(addr), &regs->iar);
	H2_INDIRECT_WAIT(regs);
	ret = hal2_read(&regs->idr0) & 0xffff;
	hal2_write(H2_READ_ADDR(addr) | 0x1, &regs->iar);
	H2_INDIRECT_WAIT(regs);
	ret |= (hal2_read(&regs->idr0) & 0xffff) << 16;
	return ret;
}