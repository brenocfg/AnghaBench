#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  unsigned long u32 ;
struct TYPE_8__ {unsigned long toc; void* tramp; } ;
struct module {TYPE_1__ arch; int /*<<< orphan*/  name; } ;
struct TYPE_11__ {int r_offset; unsigned long r_addend; int /*<<< orphan*/  r_info; } ;
struct TYPE_10__ {size_t sh_info; int sh_size; scalar_t__ sh_addr; } ;
struct TYPE_9__ {int st_name; unsigned long st_value; int /*<<< orphan*/  st_shndx; } ;
typedef  TYPE_2__ Elf64_Sym ;
typedef  TYPE_3__ Elf64_Shdr ;
typedef  TYPE_4__ Elf64_Rela ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGP (char*,...) ; 
 int ELF64_R_SYM (int /*<<< orphan*/ ) ; 
 int ELF64_R_TYPE (int /*<<< orphan*/ ) ; 
 int ENOENT ; 
 int ENOEXEC ; 
#define  R_PPC64_ADDR32 134 
#define  R_PPC64_ADDR64 133 
#define  R_PPC64_REL64 132 
#define  R_PPC64_TOC 131 
#define  R_PPC64_TOC16 130 
#define  R_PPC64_TOC16_DS 129 
#define  R_PPC_REL24 128 
 int /*<<< orphan*/  SHN_UNDEF ; 
 scalar_t__ ftrace_caller ; 
 unsigned long my_r2 (TYPE_3__*,struct module*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  restore_r2 (unsigned long*,struct module*) ; 
 void* stub_for_addr (TYPE_3__*,unsigned long,struct module*) ; 

int apply_relocate_add(Elf64_Shdr *sechdrs,
		       const char *strtab,
		       unsigned int symindex,
		       unsigned int relsec,
		       struct module *me)
{
	unsigned int i;
	Elf64_Rela *rela = (void *)sechdrs[relsec].sh_addr;
	Elf64_Sym *sym;
	unsigned long *location;
	unsigned long value;

	DEBUGP("Applying ADD relocate section %u to %u\n", relsec,
	       sechdrs[relsec].sh_info);
	for (i = 0; i < sechdrs[relsec].sh_size / sizeof(*rela); i++) {
		/* This is where to make the change */
		location = (void *)sechdrs[sechdrs[relsec].sh_info].sh_addr
			+ rela[i].r_offset;
		/* This is the symbol it is referring to */
		sym = (Elf64_Sym *)sechdrs[symindex].sh_addr
			+ ELF64_R_SYM(rela[i].r_info);

		DEBUGP("RELOC at %p: %li-type as %s (%lu) + %li\n",
		       location, (long)ELF64_R_TYPE(rela[i].r_info),
		       strtab + sym->st_name, (unsigned long)sym->st_value,
		       (long)rela[i].r_addend);

		/* `Everything is relative'. */
		value = sym->st_value + rela[i].r_addend;

		switch (ELF64_R_TYPE(rela[i].r_info)) {
		case R_PPC64_ADDR32:
			/* Simply set it */
			*(u32 *)location = value;
			break;

		case R_PPC64_ADDR64:
			/* Simply set it */
			*(unsigned long *)location = value;
			break;

		case R_PPC64_TOC:
			*(unsigned long *)location = my_r2(sechdrs, me);
			break;

		case R_PPC64_TOC16:
			/* Subtract TOC pointer */
			value -= my_r2(sechdrs, me);
			if (value + 0x8000 > 0xffff) {
				printk("%s: bad TOC16 relocation (%lu)\n",
				       me->name, value);
				return -ENOEXEC;
			}
			*((uint16_t *) location)
				= (*((uint16_t *) location) & ~0xffff)
				| (value & 0xffff);
			break;

		case R_PPC64_TOC16_DS:
			/* Subtract TOC pointer */
			value -= my_r2(sechdrs, me);
			if ((value & 3) != 0 || value + 0x8000 > 0xffff) {
				printk("%s: bad TOC16_DS relocation (%lu)\n",
				       me->name, value);
				return -ENOEXEC;
			}
			*((uint16_t *) location)
				= (*((uint16_t *) location) & ~0xfffc)
				| (value & 0xfffc);
			break;

		case R_PPC_REL24:
			/* FIXME: Handle weak symbols here --RR */
			if (sym->st_shndx == SHN_UNDEF) {
				/* External: go via stub */
				value = stub_for_addr(sechdrs, value, me);
				if (!value)
					return -ENOENT;
				if (!restore_r2((u32 *)location + 1, me))
					return -ENOEXEC;
			}

			/* Convert value to relative */
			value -= (unsigned long)location;
			if (value + 0x2000000 > 0x3ffffff || (value & 3) != 0){
				printk("%s: REL24 %li out of range!\n",
				       me->name, (long int)value);
				return -ENOEXEC;
			}

			/* Only replace bits 2 through 26 */
			*(uint32_t *)location
				= (*(uint32_t *)location & ~0x03fffffc)
				| (value & 0x03fffffc);
			break;

		case R_PPC64_REL64:
			/* 64 bits relative (used by features fixups) */
			*location = value - (unsigned long)location;
			break;

		default:
			printk("%s: Unknown ADD relocation: %lu\n",
			       me->name,
			       (unsigned long)ELF64_R_TYPE(rela[i].r_info));
			return -ENOEXEC;
		}
	}

#ifdef CONFIG_DYNAMIC_FTRACE
	me->arch.toc = my_r2(sechdrs, me);
	me->arch.tramp = stub_for_addr(sechdrs,
				       (unsigned long)ftrace_caller,
				       me);
#endif

	return 0;
}