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
typedef  int /*<<< orphan*/  Xsig ;

/* Variables and functions */

__attribute__((used)) static inline void add_two_Xsig(Xsig *dest, const Xsig *x2, long int *exp)
{
	asm volatile ("movl %2,%%ecx; movl %3,%%esi;\n"
		      "movl (%%esi),%%eax; addl %%eax,(%%ecx);\n"
		      "movl 4(%%esi),%%eax; adcl %%eax,4(%%ecx);\n"
		      "movl 8(%%esi),%%eax; adcl %%eax,8(%%ecx);\n"
		      "jnc 0f;\n"
		      "rcrl 8(%%ecx); rcrl 4(%%ecx); rcrl (%%ecx)\n"
		      "movl %4,%%ecx; incl (%%ecx)\n"
		      "movl $1,%%eax; jmp 1f;\n"
		      "0: xorl %%eax,%%eax;\n" "1:\n":"=g" (*exp), "=g"(*dest)
		      :"g"(dest), "g"(x2), "g"(exp)
		      :"cx", "si", "ax");
}