#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd_reloc_status_type ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_11__ {TYPE_2__* section; } ;
typedef  TYPE_3__ asymbol ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_12__ {int addend; } ;
typedef  TYPE_4__ arelent ;
struct TYPE_10__ {TYPE_1__* output_section; } ;
struct TYPE_9__ {scalar_t__ vma; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_elf_generic_reloc (int /*<<< orphan*/ *,TYPE_4__*,TYPE_3__*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  bfd_reloc_continue ; 

__attribute__((used)) static bfd_reloc_status_type
ppc64_elf_sectoff_ha_reloc (bfd *abfd, arelent *reloc_entry, asymbol *symbol,
			    void *data, asection *input_section,
			    bfd *output_bfd, char **error_message)
{
  /* If this is a relocatable link (output_bfd test tells us), just
     call the generic function.  Any adjustment will be done at final
     link time.  */
  if (output_bfd != NULL)
    return bfd_elf_generic_reloc (abfd, reloc_entry, symbol, data,
				  input_section, output_bfd, error_message);

  /* Subtract the symbol section base address.  */
  reloc_entry->addend -= symbol->section->output_section->vma;

  /* Adjust the addend for sign extension of the low 16 bits.  */
  reloc_entry->addend += 0x8000;
  return bfd_reloc_continue;
}