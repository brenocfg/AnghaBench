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
struct pt_regs {int dummy; } ;
struct fadump_reg_entry {scalar_t__ reg_id; int /*<<< orphan*/  reg_value; } ;

/* Variables and functions */
 scalar_t__ REG_ID (char*) ; 
 int /*<<< orphan*/  fadump_set_regval (struct pt_regs*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct pt_regs*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct fadump_reg_entry*
fadump_read_registers(struct fadump_reg_entry *reg_entry, struct pt_regs *regs)
{
	memset(regs, 0, sizeof(struct pt_regs));

	while (reg_entry->reg_id != REG_ID("CPUEND")) {
		fadump_set_regval(regs, reg_entry->reg_id,
					reg_entry->reg_value);
		reg_entry++;
	}
	reg_entry++;
	return reg_entry;
}