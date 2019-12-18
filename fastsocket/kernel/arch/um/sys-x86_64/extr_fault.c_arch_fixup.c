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
struct uml_pt_regs {int dummy; } ;
struct exception_table_entry {int /*<<< orphan*/  fixup; } ;
typedef  int /*<<< orphan*/  UPT_IP ;

/* Variables and functions */
 struct exception_table_entry* search_exception_tables (unsigned long) ; 

int arch_fixup(unsigned long address, struct uml_pt_regs *regs)
{
	const struct exception_table_entry *fixup;

	fixup = search_exception_tables(address);
	if (fixup != 0) {
		UPT_IP(regs) = fixup->fixup;
		return 1;
	}
	return 0;
}