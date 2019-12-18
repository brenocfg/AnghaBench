#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_5__ {char* core_command; void* core_program; } ;
struct TYPE_4__ {int descsz; int /*<<< orphan*/  descdata; } ;
typedef  TYPE_1__ Elf_Internal_Note ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 void* _bfd_elfcore_strndup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* elf_tdata (int /*<<< orphan*/ *) ; 
 int strlen (char*) ; 

__attribute__((used)) static bfd_boolean
_bfd_score_elf_grok_psinfo (bfd *abfd, Elf_Internal_Note *note)
{
  switch (note->descsz)
    {
    default:
      return FALSE;

    case 124:                  /* Linux/Score elf_prpsinfo.  */
      elf_tdata (abfd)->core_program = _bfd_elfcore_strndup (abfd, note->descdata + 28, 16);
      elf_tdata (abfd)->core_command = _bfd_elfcore_strndup (abfd, note->descdata + 44, 80);
    }

  /* Note that for some reason, a spurious space is tacked
     onto the end of the args in some (at least one anyway)
     implementations, so strip it off if it exists.  */

  {
    char *command = elf_tdata (abfd)->core_command;
    int n = strlen (command);

    if (0 < n && command[n - 1] == ' ')
      command[n - 1] = '\0';
  }

  return TRUE;
}