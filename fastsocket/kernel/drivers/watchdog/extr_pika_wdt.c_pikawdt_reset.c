#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ fpga; } ;

/* Variables and functions */
 int WDT_HW_TIMEOUT ; 
 unsigned int in_be32 (scalar_t__) ; 
 int /*<<< orphan*/  out_be32 (scalar_t__,unsigned int) ; 
 TYPE_1__ pikawdt_private ; 

__attribute__((used)) static inline void pikawdt_reset(void)
{
	/* -- FPGA: Reset Control Register (32bit R/W) (Offset: 0x14) --
	 * Bit 7,    WTCHDG_EN: When set to 1, the watchdog timer is enabled.
	 *           Once enabled, it cannot be disabled. The watchdog can be
	 *           kicked by performing any write access to the reset
	 *           control register (this register).
	 * Bit 8-11, WTCHDG_TIMEOUT_SEC: Sets the watchdog timeout value in
	 *           seconds. Valid ranges are 1 to 15 seconds. The value can
	 *           be modified dynamically.
	 */
	unsigned reset = in_be32(pikawdt_private.fpga + 0x14);
	/* enable with max timeout - 15 seconds */
	reset |= (1 << 7) + (WDT_HW_TIMEOUT << 8);
	out_be32(pikawdt_private.fpga + 0x14, reset);
}