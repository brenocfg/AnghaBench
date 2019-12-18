#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd_reloc_status_type ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asymbol ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_4__ {scalar_t__ address; int /*<<< orphan*/  addend; } ;
typedef  TYPE_1__ arelent ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_elf_generic_reloc (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char**) ; 

__attribute__((used)) static bfd_reloc_status_type
arc_elf_b22_pcrel (bfd * abfd,
		   arelent * reloc_entry,
		   asymbol * symbol,
		   void * data,
		   asection * input_section,
		   bfd * output_bfd,
		   char ** error_message)
{
  /* If linking, back up the final symbol address by the address of the
     reloc.  This cannot be accomplished by setting the pcrel_offset
     field to TRUE, as bfd_install_relocation will detect this and refuse
     to install the offset in the first place, but bfd_perform_relocation
     will still insist on removing it.  */
  if (output_bfd == NULL)
    reloc_entry->addend -= reloc_entry->address;

  /* Fall through to the default elf reloc handler.  */
  return bfd_elf_generic_reloc (abfd, reloc_entry, symbol, data,
				input_section, output_bfd, error_message);
}