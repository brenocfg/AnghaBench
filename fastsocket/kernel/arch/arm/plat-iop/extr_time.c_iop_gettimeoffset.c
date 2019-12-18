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
 unsigned long next_jiffy_time ; 
 unsigned long read_tcr1 () ; 
 unsigned long ticks_per_usec ; 

unsigned long iop_gettimeoffset(void)
{
	unsigned long offset, temp;

	/* enable cp6, if necessary, to avoid taking the overhead of an
	 * undefined instruction trap
	 */
	asm volatile (
	"mrc	p15, 0, %0, c15, c1, 0\n\t"
	"tst	%0, #(1 << 6)\n\t"
	"orreq	%0, %0, #(1 << 6)\n\t"
	"mcreq	p15, 0, %0, c15, c1, 0\n\t"
#ifdef CONFIG_CPU_XSCALE
	"mrceq	p15, 0, %0, c15, c1, 0\n\t"
	"moveq	%0, %0\n\t"
	"subeq	pc, pc, #4\n\t"
#endif
	: "=r"(temp) : : "cc");

	offset = next_jiffy_time - read_tcr1();

	return offset / ticks_per_usec;
}