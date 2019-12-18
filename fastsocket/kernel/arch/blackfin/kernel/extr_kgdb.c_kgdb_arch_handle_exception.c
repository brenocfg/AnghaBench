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
struct pt_regs {long retx; int syscfg; int ipend; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfin_correct_hw_break () ; 
 int /*<<< orphan*/ * current ; 
 int /*<<< orphan*/ * kgdb_contthread ; 
 int /*<<< orphan*/  kgdb_hex2long (char**,long*) ; 
 int kgdb_single_step ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

int kgdb_arch_handle_exception(int vector, int signo,
			       int err_code, char *remcom_in_buffer,
			       char *remcom_out_buffer,
			       struct pt_regs *regs)
{
	long addr;
	char *ptr;
	int newPC;
	int i;

	switch (remcom_in_buffer[0]) {
	case 'c':
	case 's':
		if (kgdb_contthread && kgdb_contthread != current) {
			strcpy(remcom_out_buffer, "E00");
			break;
		}

		kgdb_contthread = NULL;

		/* try to read optional parameter, pc unchanged if no parm */
		ptr = &remcom_in_buffer[1];
		if (kgdb_hex2long(&ptr, &addr)) {
			regs->retx = addr;
		}
		newPC = regs->retx;

		/* clear the trace bit */
		regs->syscfg &= 0xfffffffe;

		/* set the trace bit if we're stepping */
		if (remcom_in_buffer[0] == 's') {
			regs->syscfg |= 0x1;
			kgdb_single_step = regs->ipend;
			kgdb_single_step >>= 6;
			for (i = 10; i > 0; i--, kgdb_single_step >>= 1)
				if (kgdb_single_step & 1)
					break;
			/* i indicate event priority of current stopped instruction
			 * user space instruction is 0, IVG15 is 1, IVTMR is 10.
			 * kgdb_single_step > 0 means in single step mode
			 */
			kgdb_single_step = i + 1;
		}

		bfin_correct_hw_break();

		return 0;
	}			/* switch */
	return -1;		/* this means that we do not want to exit from the handler */
}