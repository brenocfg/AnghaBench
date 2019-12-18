#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ pcrel_offset; scalar_t__ pc_relative; } ;
typedef  TYPE_2__ reloc_howto_type ;
typedef  scalar_t__ bfd_vma ;
typedef  int /*<<< orphan*/  bfd_reloc_status_type ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_10__ {scalar_t__ output_offset; TYPE_1__* output_section; } ;
typedef  TYPE_3__ asection ;
struct TYPE_8__ {scalar_t__ vma; } ;

/* Variables and functions */
 int /*<<< orphan*/  _bfd_relocate_contents (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_get_section_limit (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  bfd_reloc_outofrange ; 

bfd_reloc_status_type
_bfd_final_link_relocate (reloc_howto_type *howto,
			  bfd *input_bfd,
			  asection *input_section,
			  bfd_byte *contents,
			  bfd_vma address,
			  bfd_vma value,
			  bfd_vma addend)
{
  bfd_vma relocation;

  /* Sanity check the address.  */
  if (address > bfd_get_section_limit (input_bfd, input_section))
    return bfd_reloc_outofrange;

  /* This function assumes that we are dealing with a basic relocation
     against a symbol.  We want to compute the value of the symbol to
     relocate to.  This is just VALUE, the value of the symbol, plus
     ADDEND, any addend associated with the reloc.  */
  relocation = value + addend;

  /* If the relocation is PC relative, we want to set RELOCATION to
     the distance between the symbol (currently in RELOCATION) and the
     location we are relocating.  Some targets (e.g., i386-aout)
     arrange for the contents of the section to be the negative of the
     offset of the location within the section; for such targets
     pcrel_offset is FALSE.  Other targets (e.g., m88kbcs or ELF)
     simply leave the contents of the section as zero; for such
     targets pcrel_offset is TRUE.  If pcrel_offset is FALSE we do not
     need to subtract out the offset of the location within the
     section (which is just ADDRESS).  */
  if (howto->pc_relative)
    {
      relocation -= (input_section->output_section->vma
		     + input_section->output_offset);
      if (howto->pcrel_offset)
	relocation -= address;
    }

  return _bfd_relocate_contents (howto, input_bfd, relocation,
				 contents + address);
}