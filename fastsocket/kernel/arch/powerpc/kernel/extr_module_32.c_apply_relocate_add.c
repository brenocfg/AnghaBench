#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_7__ {void* tramp; } ;
struct module {int* module_core; TYPE_1__ arch; int /*<<< orphan*/  name; } ;
struct TYPE_10__ {int r_offset; int r_addend; int /*<<< orphan*/  r_info; } ;
struct TYPE_9__ {size_t sh_info; int sh_size; scalar_t__ sh_addr; } ;
struct TYPE_8__ {int st_value; } ;
typedef  TYPE_2__ Elf32_Sym ;
typedef  TYPE_3__ Elf32_Shdr ;
typedef  TYPE_4__ Elf32_Rela ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGP (char*,int,...) ; 
 int ELF32_R_SYM (int /*<<< orphan*/ ) ; 
 int ELF32_R_TYPE (int /*<<< orphan*/ ) ; 
 int ENOEXEC ; 
#define  R_PPC_ADDR16_HA 133 
#define  R_PPC_ADDR16_HI 132 
#define  R_PPC_ADDR16_LO 131 
#define  R_PPC_ADDR32 130 
#define  R_PPC_REL24 129 
#define  R_PPC_REL32 128 
 void* do_plt_call (int*,unsigned long,TYPE_3__*,struct module*) ; 
 scalar_t__ ftrace_caller ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int) ; 

int apply_relocate_add(Elf32_Shdr *sechdrs,
		       const char *strtab,
		       unsigned int symindex,
		       unsigned int relsec,
		       struct module *module)
{
	unsigned int i;
	Elf32_Rela *rela = (void *)sechdrs[relsec].sh_addr;
	Elf32_Sym *sym;
	uint32_t *location;
	uint32_t value;

	DEBUGP("Applying ADD relocate section %u to %u\n", relsec,
	       sechdrs[relsec].sh_info);
	for (i = 0; i < sechdrs[relsec].sh_size / sizeof(*rela); i++) {
		/* This is where to make the change */
		location = (void *)sechdrs[sechdrs[relsec].sh_info].sh_addr
			+ rela[i].r_offset;
		/* This is the symbol it is referring to.  Note that all
		   undefined symbols have been resolved.  */
		sym = (Elf32_Sym *)sechdrs[symindex].sh_addr
			+ ELF32_R_SYM(rela[i].r_info);
		/* `Everything is relative'. */
		value = sym->st_value + rela[i].r_addend;

		switch (ELF32_R_TYPE(rela[i].r_info)) {
		case R_PPC_ADDR32:
			/* Simply set it */
			*(uint32_t *)location = value;
			break;

		case R_PPC_ADDR16_LO:
			/* Low half of the symbol */
			*(uint16_t *)location = value;
			break;

		case R_PPC_ADDR16_HI:
			/* Higher half of the symbol */
			*(uint16_t *)location = (value >> 16);
			break;

		case R_PPC_ADDR16_HA:
			/* Sign-adjusted lower 16 bits: PPC ELF ABI says:
			   (((x >> 16) + ((x & 0x8000) ? 1 : 0))) & 0xFFFF.
			   This is the same, only sane.
			 */
			*(uint16_t *)location = (value + 0x8000) >> 16;
			break;

		case R_PPC_REL24:
			if ((int)(value - (uint32_t)location) < -0x02000000
			    || (int)(value - (uint32_t)location) >= 0x02000000)
				value = do_plt_call(location, value,
						    sechdrs, module);

			/* Only replace bits 2 through 26 */
			DEBUGP("REL24 value = %08X. location = %08X\n",
			       value, (uint32_t)location);
			DEBUGP("Location before: %08X.\n",
			       *(uint32_t *)location);
			*(uint32_t *)location
				= (*(uint32_t *)location & ~0x03fffffc)
				| ((value - (uint32_t)location)
				   & 0x03fffffc);
			DEBUGP("Location after: %08X.\n",
			       *(uint32_t *)location);
			DEBUGP("ie. jump to %08X+%08X = %08X\n",
			       *(uint32_t *)location & 0x03fffffc,
			       (uint32_t)location,
			       (*(uint32_t *)location & 0x03fffffc)
			       + (uint32_t)location);
			break;

		case R_PPC_REL32:
			/* 32-bit relative jump. */
			*(uint32_t *)location = value - (uint32_t)location;
			break;

		default:
			printk("%s: unknown ADD relocation: %u\n",
			       module->name,
			       ELF32_R_TYPE(rela[i].r_info));
			return -ENOEXEC;
		}
	}
#ifdef CONFIG_DYNAMIC_FTRACE
	module->arch.tramp =
		do_plt_call(module->module_core,
			    (unsigned long)ftrace_caller,
			    sechdrs, module);
#endif
	return 0;
}