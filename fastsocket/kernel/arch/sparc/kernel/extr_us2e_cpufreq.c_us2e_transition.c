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
 int /*<<< orphan*/  BUG () ; 
 unsigned long ESTAR_MODE_DIV_2 ; 
 unsigned long ESTAR_MODE_DIV_MASK ; 
 int /*<<< orphan*/  HBIRD_ESTAR_MODE_ADDR ; 
 int /*<<< orphan*/  frob_mem_refresh (int,unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  self_refresh_ctl (int) ; 
 int /*<<< orphan*/  write_hbreg (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void us2e_transition(unsigned long estar, unsigned long new_bits,
			    unsigned long clock_tick,
			    unsigned long old_divisor, unsigned long divisor)
{
	unsigned long flags;

	local_irq_save(flags);

	estar &= ~ESTAR_MODE_DIV_MASK;

	/* This is based upon the state transition diagram in the IIe manual.  */
	if (old_divisor == 2 && divisor == 1) {
		self_refresh_ctl(0);
		write_hbreg(HBIRD_ESTAR_MODE_ADDR, estar | new_bits);
		frob_mem_refresh(0, clock_tick, old_divisor, divisor);
	} else if (old_divisor == 1 && divisor == 2) {
		frob_mem_refresh(1, clock_tick, old_divisor, divisor);
		write_hbreg(HBIRD_ESTAR_MODE_ADDR, estar | new_bits);
		self_refresh_ctl(1);
	} else if (old_divisor == 1 && divisor > 2) {
		us2e_transition(estar, ESTAR_MODE_DIV_2, clock_tick,
				1, 2);
		us2e_transition(estar, new_bits, clock_tick,
				2, divisor);
	} else if (old_divisor > 2 && divisor == 1) {
		us2e_transition(estar, ESTAR_MODE_DIV_2, clock_tick,
				old_divisor, 2);
		us2e_transition(estar, new_bits, clock_tick,
				2, divisor);
	} else if (old_divisor < divisor) {
		frob_mem_refresh(0, clock_tick, old_divisor, divisor);
		write_hbreg(HBIRD_ESTAR_MODE_ADDR, estar | new_bits);
	} else if (old_divisor > divisor) {
		write_hbreg(HBIRD_ESTAR_MODE_ADDR, estar | new_bits);
		frob_mem_refresh(1, clock_tick, old_divisor, divisor);
	} else {
		BUG();
	}

	local_irq_restore(flags);
}