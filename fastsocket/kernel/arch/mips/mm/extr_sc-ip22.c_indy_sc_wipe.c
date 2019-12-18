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

__attribute__((used)) static inline void indy_sc_wipe(unsigned long first, unsigned long last)
{
	unsigned long tmp;

	__asm__ __volatile__(
	".set\tpush\t\t\t# indy_sc_wipe\n\t"
	".set\tnoreorder\n\t"
	".set\tmips3\n\t"
	".set\tnoat\n\t"
	"mfc0\t%2, $12\n\t"
	"li\t$1, 0x80\t\t\t# Go 64 bit\n\t"
	"mtc0\t$1, $12\n\t"

	"dli\t$1, 0x9000000080000000\n\t"
	"or\t%0, $1\t\t\t# first line to flush\n\t"
	"or\t%1, $1\t\t\t# last line to flush\n\t"
	".set\tat\n\t"

	"1:\tsw\t$0, 0(%0)\n\t"
	"bne\t%0, %1, 1b\n\t"
	" daddu\t%0, 32\n\t"

	"mtc0\t%2, $12\t\t\t# Back to 32 bit\n\t"
	"nop; nop; nop; nop;\n\t"
	".set\tpop"
	: "=r" (first), "=r" (last), "=&r" (tmp)
	: "0" (first), "1" (last));
}