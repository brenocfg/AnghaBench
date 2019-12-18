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
 long __NR_execve ; 

int kernel_execve(const char *file, char **argv, char **envp)
{
	register long scno asm("r8") = __NR_execve;
	register long sc1 asm("r12") = (long)file;
	register long sc2 asm("r11") = (long)argv;
	register long sc3 asm("r10") = (long)envp;

	asm volatile("scall"
		     : "=r"(sc1)
		     : "r"(scno), "0"(sc1), "r"(sc2), "r"(sc3)
		     : "cc", "memory");
	return sc1;
}