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

void __delay(unsigned long loops)
{
#ifdef CONFIG_ISA_DUAL_ISSUE
	__asm__ __volatile__ (
		"beqz	%0, 2f			\n\t"
		"addi	%0, #-1			\n\t"

		" .fillinsn			\n\t"
		"1:				\n\t"
		"cmpz	%0  ||  addi  %0, #-1	\n\t"
		"bc	2f  ||  cmpz  %0	\n\t"
		"bc	2f  ||  addi  %0, #-1	\n\t"
		"cmpz	%0  ||  addi  %0, #-1	\n\t"
		"bc	2f  ||  cmpz  %0	\n\t"
		"bnc	1b  ||  addi  %0, #-1	\n\t"
		" .fillinsn			\n\t"
		"2:				\n\t"
		: "+r" (loops)
		: "r" (0)
		: "cbit"
	);
#else
	__asm__ __volatile__ (
		"beqz	%0, 2f			\n\t"
		" .fillinsn			\n\t"
		"1:				\n\t"
		"addi	%0, #-1			\n\t"
		"blez	%0, 2f			\n\t"
		"addi	%0, #-1			\n\t"
		"blez	%0, 2f			\n\t"
		"addi	%0, #-1			\n\t"
		"blez	%0, 2f			\n\t"
		"addi	%0, #-1			\n\t"
		"bgtz	%0, 1b			\n\t"
		" .fillinsn			\n\t"
		"2:				\n\t"
		: "+r" (loops)
		: "r" (0)
	);
#endif
}