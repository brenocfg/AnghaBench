#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int flagword ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {int e_flags; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ARRAY_SIZE (char**) ; 
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 int EF_MEP_CPU_MASK ; 
 int EF_MEP_INDEX_MASK ; 
 int /*<<< orphan*/  TRUE ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  _bfd_elf_print_private_bfd_data (int /*<<< orphan*/ *,void*) ; 
 char** config_names ; 
 char** core_names ; 
 TYPE_1__* elf_elfheader (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bfd_boolean
mep_elf_print_private_bfd_data (bfd * abfd, void * ptr)
{
  FILE *   file = (FILE *) ptr;
  flagword flags, partial_flags;

  BFD_ASSERT (abfd != NULL && ptr != NULL);

  /* Print normal ELF private data.  */
  _bfd_elf_print_private_bfd_data (abfd, ptr);

  flags = elf_elfheader (abfd)->e_flags;
  fprintf (file, _("private flags = 0x%lx"), (long)flags);

  partial_flags = (flags & EF_MEP_CPU_MASK) >> 24;
  if (partial_flags < ARRAY_SIZE (core_names))
    fprintf (file, "  core: %s", core_names[(long)partial_flags]);

  partial_flags = flags & EF_MEP_INDEX_MASK;
  if (partial_flags < ARRAY_SIZE (config_names))
    fprintf (file, "  me_module: %s", config_names[(long)partial_flags]);

  fputc ('\n', file);

  return TRUE;
}