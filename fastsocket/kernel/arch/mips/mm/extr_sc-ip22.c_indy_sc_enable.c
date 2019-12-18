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
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static void indy_sc_enable(void)
{
	unsigned long addr, tmp1, tmp2;

	/* This is really cool... */
#ifdef DEBUG_CACHE
	printk("Enabling R4600 SCACHE\n");
#endif
	__asm__ __volatile__(
	".set\tpush\n\t"
	".set\tnoreorder\n\t"
	".set\tmips3\n\t"
	"mfc0\t%2, $12\n\t"
	"nop; nop; nop; nop;\n\t"
	"li\t%1, 0x80\n\t"
	"mtc0\t%1, $12\n\t"
	"nop; nop; nop; nop;\n\t"
	"li\t%0, 0x1\n\t"
	"dsll\t%0, 31\n\t"
	"lui\t%1, 0x9000\n\t"
	"dsll32\t%1, 0\n\t"
	"or\t%0, %1, %0\n\t"
	"sb\t$0, 0(%0)\n\t"
	"mtc0\t$0, $12\n\t"
	"nop; nop; nop; nop;\n\t"
	"mtc0\t%2, $12\n\t"
	"nop; nop; nop; nop;\n\t"
	".set\tpop"
	: "=r" (tmp1), "=r" (tmp2), "=r" (addr));
}