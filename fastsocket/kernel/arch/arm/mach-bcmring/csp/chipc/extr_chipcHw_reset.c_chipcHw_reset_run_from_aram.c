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

/* Variables and functions */

void chipcHw_reset_run_from_aram(void)
{
/* Make sure, pipeline is filled with instructions coming from ARAM */
__asm (" nop                                                            \n\t"
		" nop                                                            \n\t"
#if defined(__KERNEL__) && !defined(STANDALONE)
		" MRC      p15,#0x0,r0,c1,c0,#0                                  \n\t"
		" BIC      r0,r0,#0xd                                            \n\t"
		" MCR      p15,#0x0,r0,c1,c0,#0                                  \n\t"
		" nop                                                            \n\t"
		" nop                                                            \n\t"
		" nop                                                            \n\t"
		" nop                                                            \n\t"
		" nop                                                            \n\t"
		" nop                                                            \n\t"
#endif
		" nop                                                            \n\t"
		" nop                                                            \n\t"
/* Bypass the ARM clock and switch to XTAL clock */
		" MOV      r2,#0x80000000                                        \n\t"
		" LDR      r3,[r2,#8]                                            \n\t"
		" ORR      r3,r3,#0x20000                                        \n\t"
		" STR      r3,[r2,#8]                                            \n\t"

		" nop                                                            \n\t"
		" nop                                                            \n\t"
		" nop                                                            \n\t"
		" nop                                                            \n\t"
		" nop                                                            \n\t"
		" nop                                                            \n\t"
		" nop                                                            \n\t"
		" nop                                                            \n\t"
		" nop                                                            \n\t"
		" nop                                                            \n\t"
		" nop                                                            \n\t"
		" nop                                                            \n\t"
		" nop                                                            \n\t"
		" nop                                                            \n\t"
		" nop                                                            \n\t"
		" nop                                                            \n\t"
		" nop                                                            \n\t"
		" nop                                                            \n\t"
		" nop                                                            \n\t"
		" nop                                                            \n\t"
/* Issue reset */
		" MOV      r3,#0x2                                               \n\t"
		" STR      r3,[r2,#0x80]                                         \n\t"
/* End here */
		" MOV      pc,pc                                                 \n\t");
/* 0xe1a0f00f ==  asm ("mov r15, r15"); */
}