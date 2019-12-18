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
 unsigned long read_c0_status () ; 
 int /*<<< orphan*/  write_c0_status (unsigned long) ; 

__attribute__((used)) static inline void modify_cp0_intmask(unsigned clr_mask, unsigned set_mask)
{
	unsigned long status = read_c0_status();

	status &= ~((clr_mask & 0xFF) << 8);
	status |= (set_mask & 0xFF) << 8;

	write_c0_status(status);
}