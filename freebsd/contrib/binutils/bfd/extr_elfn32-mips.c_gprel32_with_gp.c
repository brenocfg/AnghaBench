#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ bfd_vma ;
typedef  int /*<<< orphan*/  bfd_reloc_status_type ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  scalar_t__ bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_13__ {int flags; TYPE_9__* section; scalar_t__ value; } ;
typedef  TYPE_3__ asymbol ;
struct TYPE_14__ {int output_offset; } ;
typedef  TYPE_4__ asection ;
struct TYPE_15__ {scalar_t__ address; scalar_t__ addend; TYPE_2__* howto; } ;
typedef  TYPE_5__ arelent ;
struct TYPE_16__ {scalar_t__ output_offset; TYPE_1__* output_section; } ;
struct TYPE_12__ {scalar_t__ src_mask; } ;
struct TYPE_11__ {scalar_t__ vma; } ;

/* Variables and functions */
 int BSF_SECTION_SYM ; 
 unsigned long bfd_get_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_get_section_limit (int /*<<< orphan*/ *,TYPE_4__*) ; 
 scalar_t__ bfd_is_com_section (TYPE_9__*) ; 
 int /*<<< orphan*/  bfd_put_32 (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_reloc_ok ; 
 int /*<<< orphan*/  bfd_reloc_outofrange ; 

__attribute__((used)) static bfd_reloc_status_type
gprel32_with_gp (bfd *abfd, asymbol *symbol, arelent *reloc_entry,
		 asection *input_section, bfd_boolean relocatable,
		 void *data, bfd_vma gp)
{
  bfd_vma relocation;
  unsigned long val;

  if (bfd_is_com_section (symbol->section))
    relocation = 0;
  else
    relocation = symbol->value;

  relocation += symbol->section->output_section->vma;
  relocation += symbol->section->output_offset;

  if (reloc_entry->address > bfd_get_section_limit (abfd, input_section))
    return bfd_reloc_outofrange;

  if (reloc_entry->howto->src_mask == 0)
    val = 0;
  else
    val = bfd_get_32 (abfd, (bfd_byte *) data + reloc_entry->address);

  /* Set val to the offset into the section or symbol.  */
  val += reloc_entry->addend;

  /* Adjust val for the final section location and GP value.  If we
     are producing relocatable output, we don't want to do this for
     an external symbol.  */
  if (! relocatable
      || (symbol->flags & BSF_SECTION_SYM) != 0)
    val += relocation - gp;

  bfd_put_32 (abfd, val, (bfd_byte *) data + reloc_entry->address);

  if (relocatable)
    reloc_entry->address += input_section->output_offset;

  return bfd_reloc_ok;
}