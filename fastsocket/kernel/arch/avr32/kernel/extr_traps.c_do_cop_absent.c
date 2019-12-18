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

/* Variables and functions */
 int /*<<< orphan*/  CPUCR ; 
 int ENODEV ; 
 int sysreg_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysreg_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int do_cop_absent(u32 insn)
{
	int cop_nr;
	u32 cpucr;

	if ((insn & 0xfdf00000) == 0xf1900000)
		/* LDC0 */
		cop_nr = 0;
	else
		cop_nr = (insn >> 13) & 0x7;

	/* Try enabling the coprocessor */
	cpucr = sysreg_read(CPUCR);
	cpucr |= (1 << (24 + cop_nr));
	sysreg_write(CPUCR, cpucr);

	cpucr = sysreg_read(CPUCR);
	if (!(cpucr & (1 << (24 + cop_nr))))
		return -ENODEV;

	return 0;
}