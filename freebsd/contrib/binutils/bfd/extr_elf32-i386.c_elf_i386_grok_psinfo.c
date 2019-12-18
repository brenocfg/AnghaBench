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
struct TYPE_4__ {int namesz; int descsz; scalar_t__ descdata; int /*<<< orphan*/  namedata; } ;
typedef  TYPE_1__ Elf_Internal_Note ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 void* _bfd_elfcore_strndup (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int bfd_get_32 (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_2__* elf_tdata (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static bfd_boolean
elf_i386_grok_psinfo (bfd *abfd, Elf_Internal_Note *note)
{
  if (note->namesz == 8 && strcmp (note->namedata, "FreeBSD") == 0)
    {
      int pr_version = bfd_get_32 (abfd, note->descdata);

      if (pr_version != 1)
	return FALSE;

      elf_tdata (abfd)->core_program
	= _bfd_elfcore_strndup (abfd, note->descdata + 8, 17);
      elf_tdata (abfd)->core_command
	= _bfd_elfcore_strndup (abfd, note->descdata + 25, 81);
    }
  else
    {
      switch (note->descsz)
	{
	default:
	  return FALSE;

	case 124:		/* Linux/i386 elf_prpsinfo.  */
	  elf_tdata (abfd)->core_program
	    = _bfd_elfcore_strndup (abfd, note->descdata + 28, 16);
	  elf_tdata (abfd)->core_command
	    = _bfd_elfcore_strndup (abfd, note->descdata + 44, 80);
	}
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