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
 int /*<<< orphan*/  CVMX_IPD_CLK_COUNT ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  write_c0_cvmcount (int /*<<< orphan*/ ) ; 

void octeon_init_cvmcount(void)
{
	unsigned long flags;
	unsigned loops = 2;

	/* Clobber loops so GCC will not unroll the following while loop. */
	asm("" : "+r" (loops));

	local_irq_save(flags);
	/*
	 * Loop several times so we are executing from the cache,
	 * which should give more deterministic timing.
	 */
	while (loops--)
		write_c0_cvmcount(cvmx_read_csr(CVMX_IPD_CLK_COUNT));
	local_irq_restore(flags);
}