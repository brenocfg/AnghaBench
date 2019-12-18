#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ bfd_vma ;
typedef  int /*<<< orphan*/  bfd_signed_vma ;
typedef  scalar_t__ bfd_reloc_status_type ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  scalar_t__ bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_12__ {int flags; TYPE_5__* section; scalar_t__ value; } ;
typedef  TYPE_2__ asymbol ;
struct TYPE_13__ {int output_offset; } ;
typedef  TYPE_3__ asection ;
struct TYPE_14__ {scalar_t__ address; int /*<<< orphan*/  addend; TYPE_7__* howto; } ;
typedef  TYPE_4__ arelent ;
struct TYPE_16__ {scalar_t__ partial_inplace; } ;
struct TYPE_15__ {scalar_t__ output_offset; TYPE_1__* output_section; } ;
struct TYPE_11__ {scalar_t__ vma; } ;

/* Variables and functions */
 int BSF_SECTION_SYM ; 
 int /*<<< orphan*/  _bfd_mips_elf_sign_extend (int /*<<< orphan*/ ,int) ; 
 scalar_t__ _bfd_relocate_contents (TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_get_section_limit (int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ bfd_is_com_section (TYPE_5__*) ; 
 scalar_t__ bfd_reloc_ok ; 
 scalar_t__ bfd_reloc_outofrange ; 

bfd_reloc_status_type
_bfd_mips_elf_gprel16_with_gp (bfd *abfd, asymbol *symbol,
			       arelent *reloc_entry, asection *input_section,
			       bfd_boolean relocatable, void *data, bfd_vma gp)
{
  bfd_vma relocation;
  bfd_signed_vma val;
  bfd_reloc_status_type status;

  if (bfd_is_com_section (symbol->section))
    relocation = 0;
  else
    relocation = symbol->value;

  relocation += symbol->section->output_section->vma;
  relocation += symbol->section->output_offset;

  if (reloc_entry->address > bfd_get_section_limit (abfd, input_section))
    return bfd_reloc_outofrange;

  /* Set val to the offset into the section or symbol.  */
  val = reloc_entry->addend;

  _bfd_mips_elf_sign_extend (val, 16);

  /* Adjust val for the final section location and GP value.  If we
     are producing relocatable output, we don't want to do this for
     an external symbol.  */
  if (! relocatable
      || (symbol->flags & BSF_SECTION_SYM) != 0)
    val += relocation - gp;

  if (reloc_entry->howto->partial_inplace)
    {
      status = _bfd_relocate_contents (reloc_entry->howto, abfd, val,
				       (bfd_byte *) data
				       + reloc_entry->address);
      if (status != bfd_reloc_ok)
	return status;
    }
  else
    reloc_entry->addend = val;

  if (relocatable)
    reloc_entry->address += input_section->output_offset;

  return bfd_reloc_ok;
}