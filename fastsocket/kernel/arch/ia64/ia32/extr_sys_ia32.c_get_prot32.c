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
 unsigned int PROT_EXEC ; 
 unsigned int PROT_READ ; 
 unsigned int PROT_WRITE ; 

__attribute__((used)) static inline unsigned int
get_prot32 (unsigned int prot)
{
	if (prot & PROT_WRITE)
		/* on x86, PROT_WRITE implies PROT_READ which implies PROT_EEC */
		prot |= PROT_READ | PROT_WRITE | PROT_EXEC;
	else if (prot & (PROT_READ | PROT_EXEC))
		/* on x86, there is no distinction between PROT_READ and PROT_EXEC */
		prot |= (PROT_READ | PROT_EXEC);

	return prot;
}