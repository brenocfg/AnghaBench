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
 int MSR_IP ; 
 int /*<<< orphan*/  SPRN_SRR0 ; 
 int /*<<< orphan*/  SPRN_SRR1 ; 
 int /*<<< orphan*/  __flush_disable_L1 () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 

void amigaone_restart(char *cmd)
{
	local_irq_disable();

	/* Flush and disable caches. */
	__flush_disable_L1();

        /* Set SRR0 to the reset vector and turn on MSR_IP. */
	mtspr(SPRN_SRR0, 0xfff00100);
	mtspr(SPRN_SRR1, MSR_IP);

	/* Do an rfi to jump back to firmware. */
	__asm__ __volatile__("rfi" : : : "memory");

	/* Not reached. */
	while (1);
}