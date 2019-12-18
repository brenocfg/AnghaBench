#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct module {unsigned int name; } ;
struct TYPE_7__ {int r_offset; int r_addend; int /*<<< orphan*/  r_info; } ;
struct TYPE_6__ {int sh_info; int sh_size; scalar_t__ sh_addr; } ;
struct TYPE_5__ {int st_value; int /*<<< orphan*/  st_name; } ;
typedef  TYPE_1__ Elf32_Sym ;
typedef  TYPE_2__ Elf32_Shdr ;
typedef  TYPE_3__ Elf32_Rela ;

/* Variables and functions */
 int ELF32_R_SYM (int /*<<< orphan*/ ) ; 
 int ELF32_R_TYPE (int /*<<< orphan*/ ) ; 
 int ENOEXEC ; 
#define  R_XTENSA_32 164 
#define  R_XTENSA_ASM_EXPAND 163 
#define  R_XTENSA_DIFF16 162 
#define  R_XTENSA_DIFF32 161 
#define  R_XTENSA_DIFF8 160 
#define  R_XTENSA_NONE 159 
#define  R_XTENSA_PLT 158 
#define  R_XTENSA_SLOT0_ALT 157 
#define  R_XTENSA_SLOT0_OP 156 
#define  R_XTENSA_SLOT10_ALT 155 
#define  R_XTENSA_SLOT10_OP 154 
#define  R_XTENSA_SLOT11_ALT 153 
#define  R_XTENSA_SLOT11_OP 152 
#define  R_XTENSA_SLOT12_ALT 151 
#define  R_XTENSA_SLOT12_OP 150 
#define  R_XTENSA_SLOT13_ALT 149 
#define  R_XTENSA_SLOT13_OP 148 
#define  R_XTENSA_SLOT14_ALT 147 
#define  R_XTENSA_SLOT14_OP 146 
#define  R_XTENSA_SLOT1_ALT 145 
#define  R_XTENSA_SLOT1_OP 144 
#define  R_XTENSA_SLOT2_ALT 143 
#define  R_XTENSA_SLOT2_OP 142 
#define  R_XTENSA_SLOT3_ALT 141 
#define  R_XTENSA_SLOT3_OP 140 
#define  R_XTENSA_SLOT4_ALT 139 
#define  R_XTENSA_SLOT4_OP 138 
#define  R_XTENSA_SLOT5_ALT 137 
#define  R_XTENSA_SLOT5_OP 136 
#define  R_XTENSA_SLOT6_ALT 135 
#define  R_XTENSA_SLOT6_OP 134 
#define  R_XTENSA_SLOT7_ALT 133 
#define  R_XTENSA_SLOT7_OP 132 
#define  R_XTENSA_SLOT8_ALT 131 
#define  R_XTENSA_SLOT8_OP 130 
#define  R_XTENSA_SLOT9_ALT 129 
#define  R_XTENSA_SLOT9_OP 128 
 int /*<<< orphan*/  decode_calln_opcode (unsigned char*) ; 
 int /*<<< orphan*/  decode_l32r_opcode (unsigned char*) ; 
 int /*<<< orphan*/  printk (char*,unsigned int,int,...) ; 

int apply_relocate_add(Elf32_Shdr *sechdrs,
		       const char *strtab,
		       unsigned int symindex,
		       unsigned int relsec,
		       struct module *mod)
{
	unsigned int i;
        Elf32_Rela *rela = (void *)sechdrs[relsec].sh_addr;
	Elf32_Sym *sym;
	unsigned char *location;
	uint32_t value;

#ifdef DEBUG_RELOCATE
	printk("Applying relocate section %u to %u\n", relsec,
	       sechdrs[relsec].sh_info);
#endif
	for (i = 0; i < sechdrs[relsec].sh_size / sizeof(*rela); i++) {
		location = (char *)sechdrs[sechdrs[relsec].sh_info].sh_addr
			+ rela[i].r_offset;
		sym = (Elf32_Sym *)sechdrs[symindex].sh_addr
			+ ELF32_R_SYM(rela[i].r_info);
		value = sym->st_value + rela[i].r_addend;

		switch (ELF32_R_TYPE(rela[i].r_info)) {
		case R_XTENSA_NONE:
		case R_XTENSA_DIFF8:
		case R_XTENSA_DIFF16:
		case R_XTENSA_DIFF32:
		case R_XTENSA_ASM_EXPAND:
			break;

		case R_XTENSA_32:
		case R_XTENSA_PLT:
			*(uint32_t *)location += value;
			break;

		case R_XTENSA_SLOT0_OP:
			if (decode_calln_opcode(location)) {
				value -= ((unsigned long)location & -4) + 4;
				if ((value & 3) != 0 ||
				    ((value + (1 << 19)) >> 20) != 0) {
					printk("%s: relocation out of range, "
					       "section %d reloc %d "
					       "sym '%s'\n",
					       mod->name, relsec, i,
					       strtab + sym->st_name);
					return -ENOEXEC;
				}
				value = (signed int)value >> 2;
#ifdef __XTENSA_EB__
				location[0] = ((location[0] & ~0x3) |
					    ((value >> 16) & 0x3));
				location[1] = (value >> 8) & 0xff;
				location[2] = value & 0xff;
#endif
#ifdef __XTENSA_EL__
				location[0] = ((location[0] & ~0xc0) |
					    ((value << 6) & 0xc0));
				location[1] = (value >> 2) & 0xff;
				location[2] = (value >> 10) & 0xff;
#endif
			} else if (decode_l32r_opcode(location)) {
				value -= (((unsigned long)location + 3) & -4);
				if ((value & 3) != 0 ||
				    (signed int)value >> 18 != -1) {
					printk("%s: relocation out of range, "
					       "section %d reloc %d "
					       "sym '%s'\n",
					       mod->name, relsec, i,
					       strtab + sym->st_name);
					return -ENOEXEC;
				}
				value = (signed int)value >> 2;

#ifdef __XTENSA_EB__
				location[1] = (value >> 8) & 0xff;
				location[2] = value & 0xff;
#endif
#ifdef __XTENSA_EL__
				location[1] = value & 0xff;
				location[2] = (value >> 8) & 0xff;
#endif
			}
			/* FIXME: Ignore any other opcodes.  The Xtensa
			   assembler currently assumes that the linker will
			   always do relaxation and so all PC-relative
			   operands need relocations.  (The assembler also
			   writes out the tentative PC-relative values,
			   assuming no link-time relaxation, so it is usually
			   safe to ignore the relocations.)  If the
			   assembler's "--no-link-relax" flag can be made to
			   work, and if all kernel modules can be assembled
			   with that flag, then unexpected relocations could
			   be detected here.  */
			break;

		case R_XTENSA_SLOT1_OP:
		case R_XTENSA_SLOT2_OP:
		case R_XTENSA_SLOT3_OP:
		case R_XTENSA_SLOT4_OP:
		case R_XTENSA_SLOT5_OP:
		case R_XTENSA_SLOT6_OP:
		case R_XTENSA_SLOT7_OP:
		case R_XTENSA_SLOT8_OP:
		case R_XTENSA_SLOT9_OP:
		case R_XTENSA_SLOT10_OP:
		case R_XTENSA_SLOT11_OP:
		case R_XTENSA_SLOT12_OP:
		case R_XTENSA_SLOT13_OP:
		case R_XTENSA_SLOT14_OP:
			printk("%s: unexpected FLIX relocation: %u\n",
			       mod->name,
			       ELF32_R_TYPE(rela[i].r_info));
			return -ENOEXEC;

		case R_XTENSA_SLOT0_ALT:
		case R_XTENSA_SLOT1_ALT:
		case R_XTENSA_SLOT2_ALT:
		case R_XTENSA_SLOT3_ALT:
		case R_XTENSA_SLOT4_ALT:
		case R_XTENSA_SLOT5_ALT:
		case R_XTENSA_SLOT6_ALT:
		case R_XTENSA_SLOT7_ALT:
		case R_XTENSA_SLOT8_ALT:
		case R_XTENSA_SLOT9_ALT:
		case R_XTENSA_SLOT10_ALT:
		case R_XTENSA_SLOT11_ALT:
		case R_XTENSA_SLOT12_ALT:
		case R_XTENSA_SLOT13_ALT:
		case R_XTENSA_SLOT14_ALT:
			printk("%s: unexpected ALT relocation: %u\n",
			       mod->name,
			       ELF32_R_TYPE(rela[i].r_info));
			return -ENOEXEC;

		default:
			printk("%s: unexpected relocation: %u\n",
			       mod->name,
			       ELF32_R_TYPE(rela[i].r_info));
			return -ENOEXEC;
		}
	}
	return 0;
}