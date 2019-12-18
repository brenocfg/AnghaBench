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
typedef  int /*<<< orphan*/  uint32_t ;
struct ppc_plt_entry {int* jump; } ;
struct TYPE_4__ {size_t core_plt_section; size_t init_plt_section; } ;
struct module {void* module_core; int core_size; TYPE_1__ arch; } ;
struct TYPE_5__ {scalar_t__ sh_addr; } ;
typedef  TYPE_2__ Elf32_Shdr ;
typedef  int Elf32_Addr ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGP (char*,int,...) ; 
 scalar_t__ entry_matches (struct ppc_plt_entry*,int) ; 

__attribute__((used)) static uint32_t do_plt_call(void *location,
			    Elf32_Addr val,
			    Elf32_Shdr *sechdrs,
			    struct module *mod)
{
	struct ppc_plt_entry *entry;

	DEBUGP("Doing plt for call to 0x%x at 0x%x\n", val, (unsigned int)location);
	/* Init, or core PLT? */
	if (location >= mod->module_core
	    && location < mod->module_core + mod->core_size)
		entry = (void *)sechdrs[mod->arch.core_plt_section].sh_addr;
	else
		entry = (void *)sechdrs[mod->arch.init_plt_section].sh_addr;

	/* Find this entry, or if that fails, the next avail. entry */
	while (entry->jump[0]) {
		if (entry_matches(entry, val)) return (uint32_t)entry;
		entry++;
	}

	/* Stolen from Paul Mackerras as well... */
	entry->jump[0] = 0x3d600000+((val+0x8000)>>16);	/* lis r11,sym@ha */
	entry->jump[1] = 0x396b0000 + (val&0xffff);	/* addi r11,r11,sym@l*/
	entry->jump[2] = 0x7d6903a6;			/* mtctr r11 */
	entry->jump[3] = 0x4e800420;			/* bctr */

	DEBUGP("Initialized plt for 0x%x at %p\n", val, entry);
	return (uint32_t)entry;
}