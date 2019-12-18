#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_12__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_10__* hgot; TYPE_9__* hplt; } ;
struct mips_elf_link_hash_table {TYPE_11__ root; TYPE_8__* srelplt2; TYPE_7__* splt; } ;
struct bfd_link_info {int dummy; } ;
typedef  int bfd_vma ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_26__ {int /*<<< orphan*/  indx; } ;
struct TYPE_25__ {int size; int /*<<< orphan*/ * contents; } ;
struct TYPE_24__ {int output_offset; int /*<<< orphan*/ * contents; TYPE_6__* output_section; } ;
struct TYPE_23__ {int vma; } ;
struct TYPE_20__ {int value; TYPE_2__* section; } ;
struct TYPE_21__ {TYPE_3__ def; } ;
struct TYPE_22__ {TYPE_4__ u; } ;
struct TYPE_19__ {int output_offset; TYPE_1__* output_section; } ;
struct TYPE_18__ {int vma; } ;
struct TYPE_17__ {int r_offset; void* r_info; scalar_t__ r_addend; } ;
struct TYPE_15__ {int /*<<< orphan*/  indx; TYPE_5__ root; } ;
typedef  TYPE_12__ Elf_Internal_Rela ;
typedef  int /*<<< orphan*/  Elf32_External_Rela ;

/* Variables and functions */
 void* ELF32_R_INFO (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R_MIPS_32 ; 
 int /*<<< orphan*/  R_MIPS_HI16 ; 
 int /*<<< orphan*/  R_MIPS_LO16 ; 
 int /*<<< orphan*/  bfd_elf32_swap_reloca_in (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_12__*) ; 
 int /*<<< orphan*/  bfd_elf32_swap_reloca_out (int /*<<< orphan*/ *,TYPE_12__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_put_32 (int /*<<< orphan*/ *,int const,int /*<<< orphan*/ *) ; 
 struct mips_elf_link_hash_table* mips_elf_hash_table (struct bfd_link_info*) ; 
 int* mips_vxworks_exec_plt0_entry ; 

__attribute__((used)) static void
mips_vxworks_finish_exec_plt (bfd *output_bfd, struct bfd_link_info *info)
{
  Elf_Internal_Rela rela;
  bfd_byte *loc;
  bfd_vma got_value, got_value_high, got_value_low, plt_address;
  static const bfd_vma *plt_entry;
  struct mips_elf_link_hash_table *htab;

  htab = mips_elf_hash_table (info);
  plt_entry = mips_vxworks_exec_plt0_entry;

  /* Calculate the value of _GLOBAL_OFFSET_TABLE_.  */
  got_value = (htab->root.hgot->root.u.def.section->output_section->vma
	       + htab->root.hgot->root.u.def.section->output_offset
	       + htab->root.hgot->root.u.def.value);

  got_value_high = ((got_value + 0x8000) >> 16) & 0xffff;
  got_value_low = got_value & 0xffff;

  /* Calculate the address of the PLT header.  */
  plt_address = htab->splt->output_section->vma + htab->splt->output_offset;

  /* Install the PLT header.  */
  loc = htab->splt->contents;
  bfd_put_32 (output_bfd, plt_entry[0] | got_value_high, loc);
  bfd_put_32 (output_bfd, plt_entry[1] | got_value_low, loc + 4);
  bfd_put_32 (output_bfd, plt_entry[2], loc + 8);
  bfd_put_32 (output_bfd, plt_entry[3], loc + 12);
  bfd_put_32 (output_bfd, plt_entry[4], loc + 16);
  bfd_put_32 (output_bfd, plt_entry[5], loc + 20);

  /* Output the relocation for the lui of %hi(_GLOBAL_OFFSET_TABLE_).  */
  loc = htab->srelplt2->contents;
  rela.r_offset = plt_address;
  rela.r_info = ELF32_R_INFO (htab->root.hgot->indx, R_MIPS_HI16);
  rela.r_addend = 0;
  bfd_elf32_swap_reloca_out (output_bfd, &rela, loc);
  loc += sizeof (Elf32_External_Rela);

  /* Output the relocation for the following addiu of
     %lo(_GLOBAL_OFFSET_TABLE_).  */
  rela.r_offset += 4;
  rela.r_info = ELF32_R_INFO (htab->root.hgot->indx, R_MIPS_LO16);
  bfd_elf32_swap_reloca_out (output_bfd, &rela, loc);
  loc += sizeof (Elf32_External_Rela);

  /* Fix up the remaining relocations.  They may have the wrong
     symbol index for _G_O_T_ or _P_L_T_ depending on the order
     in which symbols were output.  */
  while (loc < htab->srelplt2->contents + htab->srelplt2->size)
    {
      Elf_Internal_Rela rel;

      bfd_elf32_swap_reloca_in (output_bfd, loc, &rel);
      rel.r_info = ELF32_R_INFO (htab->root.hplt->indx, R_MIPS_32);
      bfd_elf32_swap_reloca_out (output_bfd, &rel, loc);
      loc += sizeof (Elf32_External_Rela);

      bfd_elf32_swap_reloca_in (output_bfd, loc, &rel);
      rel.r_info = ELF32_R_INFO (htab->root.hgot->indx, R_MIPS_HI16);
      bfd_elf32_swap_reloca_out (output_bfd, &rel, loc);
      loc += sizeof (Elf32_External_Rela);

      bfd_elf32_swap_reloca_in (output_bfd, loc, &rel);
      rel.r_info = ELF32_R_INFO (htab->root.hgot->indx, R_MIPS_LO16);
      bfd_elf32_swap_reloca_out (output_bfd, &rel, loc);
      loc += sizeof (Elf32_External_Rela);
    }
}