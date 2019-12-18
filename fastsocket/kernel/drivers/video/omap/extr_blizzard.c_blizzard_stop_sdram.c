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
 int /*<<< orphan*/  BLIZZARD_MEM_BANK0_ACTIVATE ; 
 int /*<<< orphan*/  blizzard_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void blizzard_stop_sdram(void)
{
	blizzard_write_reg(BLIZZARD_MEM_BANK0_ACTIVATE, 0);
}