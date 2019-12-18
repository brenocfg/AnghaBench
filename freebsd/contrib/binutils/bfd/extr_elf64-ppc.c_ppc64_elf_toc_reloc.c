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
typedef  scalar_t__ bfd_vma ;
typedef  int /*<<< orphan*/  bfd_reloc_status_type ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asymbol ;
struct TYPE_9__ {TYPE_1__* output_section; } ;
typedef  TYPE_2__ asection ;
struct TYPE_10__ {int /*<<< orphan*/  addend; } ;
typedef  TYPE_3__ arelent ;
struct TYPE_8__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 scalar_t__ TOC_BASE_OFF ; 
 scalar_t__ _bfd_get_gp_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_elf_generic_reloc (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *,void*,TYPE_2__*,int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  bfd_reloc_continue ; 
 scalar_t__ ppc64_elf_toc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfd_reloc_status_type
ppc64_elf_toc_reloc (bfd *abfd, arelent *reloc_entry, asymbol *symbol,
		     void *data, asection *input_section,
		     bfd *output_bfd, char **error_message)
{
  bfd_vma TOCstart;

  /* If this is a relocatable link (output_bfd test tells us), just
     call the generic function.  Any adjustment will be done at final
     link time.  */
  if (output_bfd != NULL)
    return bfd_elf_generic_reloc (abfd, reloc_entry, symbol, data,
				  input_section, output_bfd, error_message);

  TOCstart = _bfd_get_gp_value (input_section->output_section->owner);
  if (TOCstart == 0)
    TOCstart = ppc64_elf_toc (input_section->output_section->owner);

  /* Subtract the TOC base address.  */
  reloc_entry->addend -= TOCstart + TOC_BASE_OFF;
  return bfd_reloc_continue;
}