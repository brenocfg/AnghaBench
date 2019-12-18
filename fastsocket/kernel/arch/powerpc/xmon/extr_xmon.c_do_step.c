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
struct pt_regs {int msr; int trap; int /*<<< orphan*/  nip; } ;

/* Variables and functions */
 scalar_t__ IS_RFID (unsigned int) ; 
 int MSR_IR ; 
 int MSR_PR ; 
 int MSR_SE ; 
 int MSR_SF ; 
 int emulate_step (struct pt_regs*,unsigned int) ; 
 int mread (int /*<<< orphan*/ ,unsigned int*,int) ; 
 int /*<<< orphan*/  ppc_inst_dump (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  xmon_print_symbol (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int do_step(struct pt_regs *regs)
{
	unsigned int instr;
	int stepped;

	/* check we are in 64-bit kernel mode, translation enabled */
	if ((regs->msr & (MSR_SF|MSR_PR|MSR_IR)) == (MSR_SF|MSR_IR)) {
		if (mread(regs->nip, &instr, 4) == 4) {
			stepped = emulate_step(regs, instr);
			if (stepped < 0) {
				printf("Couldn't single-step %s instruction\n",
				       (IS_RFID(instr)? "rfid": "mtmsrd"));
				return 0;
			}
			if (stepped > 0) {
				regs->trap = 0xd00 | (regs->trap & 1);
				printf("stepped to ");
				xmon_print_symbol(regs->nip, " ", "\n");
				ppc_inst_dump(regs->nip, 1, 0);
				return 0;
			}
		}
	}
	regs->msr |= MSR_SE;
	return 1;
}