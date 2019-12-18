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
struct blizzard_reg_list {int start; int end; } ;

/* Variables and functions */
 int /*<<< orphan*/ * blizzard_reg_cache ; 
 int /*<<< orphan*/  blizzard_write_reg (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _restore_regs(const struct blizzard_reg_list *list, int cnt)
{
	int i;

	for (i = 0; i < cnt; i++, list++) {
		int reg;
		for (reg = list->start; reg <= list->end; reg += 2)
			blizzard_write_reg(reg, blizzard_reg_cache[reg / 2]);
	}
}