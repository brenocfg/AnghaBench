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
struct pt_regs {int /*<<< orphan*/  pc; } ;
struct exception_table_entry {int /*<<< orphan*/  fixup; } ;

/* Variables and functions */
 int /*<<< orphan*/  die (char const*,struct pt_regs*,long) ; 
 struct exception_table_entry* search_exception_tables (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  user_mode (struct pt_regs*) ; 

__attribute__((used)) static void die_if_no_fixup(const char * str, struct pt_regs * regs, long err)
{
	if (!user_mode(regs)) {
		const struct exception_table_entry *fixup;
		fixup = search_exception_tables(regs->pc);
		if (fixup) {
			regs->pc = fixup->fixup;
			return;
		}
		die(str, regs, err);
	}
}