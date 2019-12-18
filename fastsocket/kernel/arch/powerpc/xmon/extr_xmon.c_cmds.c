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
struct pt_regs {int /*<<< orphan*/  nip; int /*<<< orphan*/  link; int /*<<< orphan*/ * gpr; } ;

/* Variables and functions */
#define  EOF 128 
 int /*<<< orphan*/  backtrace (struct pt_regs*) ; 
 int /*<<< orphan*/  bootcmds () ; 
 int /*<<< orphan*/  bpt_cmds () ; 
 int /*<<< orphan*/  cacheflush () ; 
 int /*<<< orphan*/  cpu_cmd () ; 
 int /*<<< orphan*/  csum () ; 
 int /*<<< orphan*/  do_spu_cmd () ; 
 int /*<<< orphan*/  do_step (struct pt_regs*) ; 
 int /*<<< orphan*/  dump () ; 
 int /*<<< orphan*/  dump_segments () ; 
 int /*<<< orphan*/  dump_tlb_44x () ; 
 int /*<<< orphan*/  excprint (struct pt_regs*) ; 
 int /*<<< orphan*/  flush_input () ; 
 int /*<<< orphan*/  help_string ; 
 int inchar () ; 
 int /*<<< orphan*/ * last_cmd ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  memex () ; 
 int /*<<< orphan*/  memlocate () ; 
 int /*<<< orphan*/  memops (int) ; 
 int /*<<< orphan*/  memzcan () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  proccall () ; 
 int /*<<< orphan*/  prregs (struct pt_regs*) ; 
 int /*<<< orphan*/  putchar (int) ; 
 int /*<<< orphan*/  show_mem (int /*<<< orphan*/ ) ; 
 int skipbl () ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  super_regs () ; 
 int /*<<< orphan*/  symbol_lookup () ; 
 int /*<<< orphan*/  take_input (int /*<<< orphan*/ *) ; 
 int termch ; 
 int xmon_no_auto_backtrace ; 
 int /*<<< orphan*/  xmon_puts (int /*<<< orphan*/ ) ; 
 struct pt_regs* xmon_regs ; 
 int /*<<< orphan*/  xmon_show_stack (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cmds(struct pt_regs *excp)
{
	int cmd = 0;

	last_cmd = NULL;
	xmon_regs = excp;

	if (!xmon_no_auto_backtrace) {
		xmon_no_auto_backtrace = 1;
		xmon_show_stack(excp->gpr[1], excp->link, excp->nip);
	}

	for(;;) {
#ifdef CONFIG_SMP
		printf("%x:", smp_processor_id());
#endif /* CONFIG_SMP */
		printf("mon> ");
		flush_input();
		termch = 0;
		cmd = skipbl();
		if( cmd == '\n' ) {
			if (last_cmd == NULL)
				continue;
			take_input(last_cmd);
			last_cmd = NULL;
			cmd = inchar();
		}
		switch (cmd) {
		case 'm':
			cmd = inchar();
			switch (cmd) {
			case 'm':
			case 's':
			case 'd':
				memops(cmd);
				break;
			case 'l':
				memlocate();
				break;
			case 'z':
				memzcan();
				break;
			case 'i':
				show_mem(0);
				break;
			default:
				termch = cmd;
				memex();
			}
			break;
		case 'd':
			dump();
			break;
		case 'l':
			symbol_lookup();
			break;
		case 'r':
			prregs(excp);	/* print regs */
			break;
		case 'e':
			excprint(excp);
			break;
		case 'S':
			super_regs();
			break;
		case 't':
			backtrace(excp);
			break;
		case 'f':
			cacheflush();
			break;
		case 's':
			if (do_spu_cmd() == 0)
				break;
			if (do_step(excp))
				return cmd;
			break;
		case 'x':
		case 'X':
			return cmd;
		case EOF:
			printf(" <no input ...>\n");
			mdelay(2000);
			return cmd;
		case '?':
			xmon_puts(help_string);
			break;
		case 'b':
			bpt_cmds();
			break;
		case 'C':
			csum();
			break;
		case 'c':
			if (cpu_cmd())
				return 0;
			break;
		case 'z':
			bootcmds();
			break;
		case 'p':
			proccall();
			break;
#ifdef CONFIG_PPC_STD_MMU
		case 'u':
			dump_segments();
			break;
#endif
#ifdef CONFIG_4xx
		case 'u':
			dump_tlb_44x();
			break;
#endif
		default:
			printf("Unrecognized command: ");
		        do {
				if (' ' < cmd && cmd <= '~')
					putchar(cmd);
				else
					printf("\\x%x", cmd);
				cmd = inchar();
		        } while (cmd != '\n'); 
			printf(" (type ? for help)\n");
			break;
		}
	}
}