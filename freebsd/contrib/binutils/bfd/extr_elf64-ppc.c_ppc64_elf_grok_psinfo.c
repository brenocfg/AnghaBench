#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_5__ {void* core_command; void* core_program; } ;
struct TYPE_4__ {int descsz; scalar_t__ descdata; } ;
typedef  TYPE_1__ Elf_Internal_Note ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 void* _bfd_elfcore_strndup (int /*<<< orphan*/ *,scalar_t__,int) ; 
 TYPE_3__* elf_tdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bfd_boolean
ppc64_elf_grok_psinfo (bfd *abfd, Elf_Internal_Note *note)
{
  if (note->descsz != 136)
    return FALSE;

  elf_tdata (abfd)->core_program
    = _bfd_elfcore_strndup (abfd, note->descdata + 40, 16);
  elf_tdata (abfd)->core_command
    = _bfd_elfcore_strndup (abfd, note->descdata + 56, 80);

  return TRUE;
}