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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int CPU_REMEMBER_JMP_STEPS ; 
 int CPU_REMEMBER_PC_STEPS ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  safe_gets (char*,int,char*) ; 

__attribute__((used)) static void show_help(void)
{
	printf(
		"CONT                           - Continue emulation\n"
		"SHOW                           - Show registers\n"
		"STACK                          - Show stack\n"
		"SET{PC,A,X,Y,S} hexval         - Set register value\n"
		"SET{N,V,D,I,Z,C} 0 or 1        - Set flag value\n"
		"C startaddr hexval...          - Change memory\n"
		"D [startaddr]                  - Disassemble memory\n"
		"F startaddr endaddr hexval     - Fill memory\n"
		"M [startaddr]                  - Memory list\n"
		"S startaddr endaddr hexval...  - Search memory\n");
	/* split into several printfs to avoid gcc -pedantic warning: "string length 'xxx'
	   is greater than the length '509' ISO C89 compilers are required to support" */
	printf(
		"LOOP [inneraddr]               - Disassemble a loop that contains inneraddr\n"
		"RAM startaddr endaddr          - Convert memory block into RAM\n"
		"ROM startaddr endaddr          - Convert memory block into ROM\n"
		"HARDWARE startaddr endaddr     - Convert memory block into HARDWARE\n"
		"READ filename startaddr nbytes - Read file into memory\n"
		"WRITE startaddr endaddr [file] - Write memory block to a file (memdump.dat)\n"
		"SUM startaddr endaddr          - Print sum of specified memory range\n");
#ifdef MONITOR_TRACE
	printf(
		"TRACE [filename]               - Output 6502 trace on/off\n");
#endif
#ifdef MONITOR_BREAK
	printf(
		"BPC [addr]                     - Set breakpoint at address\n"
		"BLINE [ypos] or [1000+ypos]    - Break at scanline or blink scanline\n"
		"BBRK ON or OFF                 - Breakpoint on BRK on/off\n"
		"HISTORY or H                   - List last %d executed instructions\n", CPU_REMEMBER_PC_STEPS);
	printf(
		"JUMPS                          - List last %d executed JMP/JSR\n", CPU_REMEMBER_JMP_STEPS);
	{
		char buf[100];
		safe_gets(buf, sizeof(buf), "Press return to continue: ");
	}
	printf(
		"G                              - Execute one instruction\n"
		"O                              - Step over the instruction\n"
		"R                              - Execute until return\n");
#elif !defined(NO_YPOS_BREAK_FLICKER)
	printf(
		"BLINE [1000+ypos]              - Blink scanline (8<=ypos<=247)\n");
#endif
	printf(
#ifdef MONITOR_BREAKPOINTS
		"B [argument...]                - Manage breakpoints (\"B ?\" for help)\n"
#endif
#ifdef MONITOR_ASSEMBLER
		"A [startaddr]                  - Start simple assembler\n"
#endif
		"ANTIC, GTIA, PIA, POKEY        - Display hardware registers\n"
		"DLIST [startaddr]              - Show Display List\n");
	printf(
#ifdef MONITOR_PROFILE
		"PROFILE                        - Display profiling statistics\n"
#endif
#ifdef MONITOR_HINTS
		"LABELS [command] [filename]    - Configure labels\n"
#endif
		"TSS [value]                    - Start trainer search\n"
		"TSC [value]                    - Perform when trainer value has changed\n"
		"TSN [value]                    - Perform when trainer value has NOT changed\n"
		"                                 Without [value], perform a deep trainer search\n"
		"TSP [count]                    - Print [count] possible trainer addresses\n");
	printf(
		"COLDSTART, WARMSTART           - Perform system coldstart/warmstart\n"
#ifdef HAVE_SYSTEM
		"!command                       - Execute shell command\n"
#endif
		"QUIT or EXIT                   - Quit emulator\n"
		"HELP or ?                      - This text\n");
}