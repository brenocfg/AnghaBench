#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_13__ ;

/* Type definitions */
typedef  enum elf_ppc64_reloc_type { ____Placeholder_elf_ppc64_reloc_type } elf_ppc64_reloc_type ;
typedef  scalar_t__ bfd_vma ;
typedef  int bfd_size_type ;
typedef  scalar_t__ bfd_signed_vma ;
typedef  int /*<<< orphan*/  bfd_reloc_status_type ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  scalar_t__ bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_21__ {TYPE_13__* section; scalar_t__ value; } ;
typedef  TYPE_4__ asymbol ;
struct TYPE_22__ {TYPE_3__* output_section; scalar_t__ output_offset; } ;
typedef  TYPE_5__ asection ;
struct TYPE_23__ {int address; scalar_t__ addend; TYPE_1__* howto; } ;
typedef  TYPE_6__ arelent ;
struct TYPE_20__ {scalar_t__ vma; } ;
struct TYPE_19__ {scalar_t__ vma; } ;
struct TYPE_18__ {int type; } ;
struct TYPE_17__ {scalar_t__ output_offset; TYPE_2__* output_section; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int R_PPC64_ADDR14_BRTAKEN ; 
 int R_PPC64_REL14_BRTAKEN ; 
 int /*<<< orphan*/  bfd_elf_generic_reloc (int /*<<< orphan*/ *,TYPE_6__*,TYPE_4__*,void*,TYPE_5__*,int /*<<< orphan*/ *,char**) ; 
 long bfd_get_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_is_com_section (TYPE_13__*) ; 
 int bfd_octets_per_byte (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_put_32 (int /*<<< orphan*/ *,long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ppc64_elf_branch_reloc (int /*<<< orphan*/ *,TYPE_6__*,TYPE_4__*,void*,TYPE_5__*,int /*<<< orphan*/ *,char**) ; 

__attribute__((used)) static bfd_reloc_status_type
ppc64_elf_brtaken_reloc (bfd *abfd, arelent *reloc_entry, asymbol *symbol,
			 void *data, asection *input_section,
			 bfd *output_bfd, char **error_message)
{
  long insn;
  enum elf_ppc64_reloc_type r_type;
  bfd_size_type octets;
  /* Disabled until we sort out how ld should choose 'y' vs 'at'.  */
  bfd_boolean is_power4 = FALSE;

  /* If this is a relocatable link (output_bfd test tells us), just
     call the generic function.  Any adjustment will be done at final
     link time.  */
  if (output_bfd != NULL)
    return bfd_elf_generic_reloc (abfd, reloc_entry, symbol, data,
				  input_section, output_bfd, error_message);

  octets = reloc_entry->address * bfd_octets_per_byte (abfd);
  insn = bfd_get_32 (abfd, (bfd_byte *) data + octets);
  insn &= ~(0x01 << 21);
  r_type = reloc_entry->howto->type;
  if (r_type == R_PPC64_ADDR14_BRTAKEN
      || r_type == R_PPC64_REL14_BRTAKEN)
    insn |= 0x01 << 21; /* 'y' or 't' bit, lowest bit of BO field.  */

  if (is_power4)
    {
      /* Set 'a' bit.  This is 0b00010 in BO field for branch
	 on CR(BI) insns (BO == 001at or 011at), and 0b01000
	 for branch on CTR insns (BO == 1a00t or 1a01t).  */
      if ((insn & (0x14 << 21)) == (0x04 << 21))
	insn |= 0x02 << 21;
      else if ((insn & (0x14 << 21)) == (0x10 << 21))
	insn |= 0x08 << 21;
      else
	goto out;
    }
  else
    {
      bfd_vma target = 0;
      bfd_vma from;

      if (!bfd_is_com_section (symbol->section))
	target = symbol->value;
      target += symbol->section->output_section->vma;
      target += symbol->section->output_offset;
      target += reloc_entry->addend;

      from = (reloc_entry->address
	      + input_section->output_offset
	      + input_section->output_section->vma);

      /* Invert 'y' bit if not the default.  */
      if ((bfd_signed_vma) (target - from) < 0)
	insn ^= 0x01 << 21;
    }
  bfd_put_32 (abfd, insn, (bfd_byte *) data + octets);
 out:
  return ppc64_elf_branch_reloc (abfd, reloc_entry, symbol, data,
				 input_section, output_bfd, error_message);
}