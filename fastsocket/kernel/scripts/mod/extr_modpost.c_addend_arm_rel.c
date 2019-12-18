#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct elf_info {scalar_t__ hdr; scalar_t__ symtab_start; } ;
struct TYPE_6__ {int r_addend; scalar_t__ r_offset; int /*<<< orphan*/  r_info; } ;
struct TYPE_5__ {scalar_t__ sh_addr; scalar_t__ sh_offset; } ;
typedef  TYPE_1__ Elf_Shdr ;
typedef  TYPE_2__ Elf_Rela ;

/* Variables and functions */
 scalar_t__ ELF_R_SYM (int /*<<< orphan*/ ) ; 
 unsigned int ELF_R_TYPE (int /*<<< orphan*/ ) ; 
#define  R_ARM_ABS32 129 
#define  R_ARM_PC24 128 

__attribute__((used)) static int addend_arm_rel(struct elf_info *elf, Elf_Shdr *sechdr, Elf_Rela *r)
{
	unsigned int r_typ = ELF_R_TYPE(r->r_info);

	switch (r_typ) {
	case R_ARM_ABS32:
		/* From ARM ABI: (S + A) | T */
		r->r_addend = (int)(long)
		              (elf->symtab_start + ELF_R_SYM(r->r_info));
		break;
	case R_ARM_PC24:
		/* From ARM ABI: ((S + A) | T) - P */
		r->r_addend = (int)(long)(elf->hdr +
		              sechdr->sh_offset +
		              (r->r_offset - sechdr->sh_addr));
		break;
	default:
		return 1;
	}
	return 0;
}