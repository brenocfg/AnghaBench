#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ bfd_vma ;
typedef  int /*<<< orphan*/  bfd_reloc_status_type ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_12__ {scalar_t__ value; TYPE_7__* section; } ;
typedef  TYPE_3__ asymbol ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_13__ {scalar_t__ addend; } ;
typedef  TYPE_4__ arelent ;
struct TYPE_14__ {scalar_t__ output_offset; TYPE_2__* output_section; TYPE_1__* owner; int /*<<< orphan*/  name; } ;
struct TYPE_11__ {scalar_t__ vma; } ;
struct TYPE_10__ {int flags; } ;

/* Variables and functions */
 int DYNAMIC ; 
 int /*<<< orphan*/  bfd_elf_generic_reloc (int /*<<< orphan*/ *,TYPE_4__*,TYPE_3__*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  bfd_reloc_continue ; 
 scalar_t__ opd_entry_value (TYPE_7__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bfd_reloc_status_type
ppc64_elf_branch_reloc (bfd *abfd, arelent *reloc_entry, asymbol *symbol,
			void *data, asection *input_section,
			bfd *output_bfd, char **error_message)
{
  if (output_bfd != NULL)
    return bfd_elf_generic_reloc (abfd, reloc_entry, symbol, data,
				  input_section, output_bfd, error_message);

  if (strcmp (symbol->section->name, ".opd") == 0
      && (symbol->section->owner->flags & DYNAMIC) == 0)
    {
      bfd_vma dest = opd_entry_value (symbol->section,
				      symbol->value + reloc_entry->addend,
				      NULL, NULL);
      if (dest != (bfd_vma) -1)
	reloc_entry->addend = dest - (symbol->value
				      + symbol->section->output_section->vma
				      + symbol->section->output_offset);
    }
  return bfd_reloc_continue;
}