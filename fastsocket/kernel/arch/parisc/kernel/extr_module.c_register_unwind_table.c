#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t unwind_section; int /*<<< orphan*/  unwind; int /*<<< orphan*/  got_offset; } ;
struct module {int /*<<< orphan*/  name; TYPE_1__ arch; scalar_t__ module_core; } ;
struct TYPE_5__ {int sh_size; scalar_t__ sh_addr; } ;
typedef  TYPE_2__ Elf_Shdr ;
typedef  unsigned long Elf_Addr ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGP (char*,size_t,unsigned char*,unsigned char*,unsigned long) ; 
 int /*<<< orphan*/  unwind_table_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,unsigned char*,unsigned char*) ; 

__attribute__((used)) static void
register_unwind_table(struct module *me,
		      const Elf_Shdr *sechdrs)
{
	unsigned char *table, *end;
	unsigned long gp;

	if (!me->arch.unwind_section)
		return;

	table = (unsigned char *)sechdrs[me->arch.unwind_section].sh_addr;
	end = table + sechdrs[me->arch.unwind_section].sh_size;
	gp = (Elf_Addr)me->module_core + me->arch.got_offset;

	DEBUGP("register_unwind_table(), sect = %d at 0x%p - 0x%p (gp=0x%lx)\n",
	       me->arch.unwind_section, table, end, gp);
	me->arch.unwind = unwind_table_add(me->name, 0, gp, table, end);
}