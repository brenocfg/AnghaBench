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
struct TYPE_5__ {void* core_command; void* core_program; } ;
struct TYPE_4__ {int descsz; int /*<<< orphan*/  descdata; } ;
typedef  TYPE_1__ Elf_Internal_Note ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 void* _bfd_elfcore_strndup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* elf_tdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bfd_boolean
elf32_sparc_grok_psinfo (bfd *abfd, Elf_Internal_Note *note)
{
  switch (note->descsz)
    {
    default:
      return FALSE;

    case 260:			/* Solaris prpsinfo_t.  */
      elf_tdata (abfd)->core_program
	= _bfd_elfcore_strndup (abfd, note->descdata + 84, 16);
      elf_tdata (abfd)->core_command
	= _bfd_elfcore_strndup (abfd, note->descdata + 100, 80);
      break;

    case 336:			/* Solaris psinfo_t.  */
      elf_tdata (abfd)->core_program
	= _bfd_elfcore_strndup (abfd, note->descdata + 88, 16);
      elf_tdata (abfd)->core_command
	= _bfd_elfcore_strndup (abfd, note->descdata + 104, 80);
      break;
    }

  return TRUE;
}