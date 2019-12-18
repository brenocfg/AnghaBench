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
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {int e_flags; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 int EF_SCORE_FIXDEP ; 
 int EF_SCORE_PIC ; 
 int /*<<< orphan*/  TRUE ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  _bfd_elf_print_private_bfd_data (int /*<<< orphan*/ *,void*) ; 
 TYPE_1__* elf_elfheader (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bfd_boolean
elf32_score_print_private_bfd_data (bfd *abfd, void * ptr)
{
  FILE *file = (FILE *) ptr;

  BFD_ASSERT (abfd != NULL && ptr != NULL);

  /* Print normal ELF private data.  */
  _bfd_elf_print_private_bfd_data (abfd, ptr);

  /* xgettext:c-format */
  fprintf (file, _("private flags = %lx:"), elf_elfheader (abfd)->e_flags);
  if (elf_elfheader (abfd)->e_flags & EF_SCORE_PIC)
    {
      fprintf (file, _(" [pic]"));
    }
  if (elf_elfheader (abfd)->e_flags & EF_SCORE_FIXDEP)
    {
      fprintf (file, _(" [fix dep]"));
    }
  fputc ('\n', file);

  return TRUE;
}