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
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _save_regs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blizzard_gen_regs ; 
 int /*<<< orphan*/  blizzard_pll_regs ; 

__attribute__((used)) static void blizzard_save_all_regs(void)
{
	_save_regs(blizzard_pll_regs, ARRAY_SIZE(blizzard_pll_regs));
	_save_regs(blizzard_gen_regs, ARRAY_SIZE(blizzard_gen_regs));
}