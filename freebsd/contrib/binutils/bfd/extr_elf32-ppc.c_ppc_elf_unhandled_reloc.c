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
typedef  int /*<<< orphan*/  bfd_reloc_status_type ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asymbol ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_6__ {TYPE_1__* howto; } ;
typedef  TYPE_2__ arelent ;
struct TYPE_5__ {char* name; } ;

/* Variables and functions */
 char* _ (char*) ; 
 int /*<<< orphan*/  bfd_elf_generic_reloc (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  bfd_reloc_dangerous ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static bfd_reloc_status_type
ppc_elf_unhandled_reloc (bfd *abfd,
			 arelent *reloc_entry,
			 asymbol *symbol,
			 void *data,
			 asection *input_section,
			 bfd *output_bfd,
			 char **error_message)
{
  /* If this is a relocatable link (output_bfd test tells us), just
     call the generic function.  Any adjustment will be done at final
     link time.  */
  if (output_bfd != NULL)
    return bfd_elf_generic_reloc (abfd, reloc_entry, symbol, data,
				  input_section, output_bfd, error_message);

  if (error_message != NULL)
    {
      static char buf[60];
      sprintf (buf, _("generic linker can't handle %s"),
	       reloc_entry->howto->name);
      *error_message = buf;
    }
  return bfd_reloc_dangerous;
}