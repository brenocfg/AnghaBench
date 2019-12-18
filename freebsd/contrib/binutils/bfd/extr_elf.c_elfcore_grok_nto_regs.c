#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_7__ {int alignment_power; int /*<<< orphan*/  filepos; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ asection ;
struct TYPE_9__ {long core_lwpid; } ;
struct TYPE_8__ {int /*<<< orphan*/  descpos; int /*<<< orphan*/  descsz; } ;
typedef  TYPE_2__ Elf_Internal_Note ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SEC_HAS_CONTENTS ; 
 int /*<<< orphan*/  TRUE ; 
 char* bfd_alloc (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_1__* bfd_make_section_anyway_with_flags (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 TYPE_5__* elf_tdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elfcore_maybe_make_sect (int /*<<< orphan*/ *,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,long) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static bfd_boolean
elfcore_grok_nto_regs (bfd *abfd,
		       Elf_Internal_Note *note,
		       long tid,
		       char *base)
{
  char buf[100];
  char *name;
  asection *sect;

  /* Make a "(base)/%d" section.  */
  sprintf (buf, "%s/%ld", base, tid);

  name = bfd_alloc (abfd, strlen (buf) + 1);
  if (name == NULL)
    return FALSE;
  strcpy (name, buf);

  sect = bfd_make_section_anyway_with_flags (abfd, name, SEC_HAS_CONTENTS);
  if (sect == NULL)
    return FALSE;

  sect->size            = note->descsz;
  sect->filepos         = note->descpos;
  sect->alignment_power = 2;

  /* This is the current thread.  */
  if (elf_tdata (abfd)->core_lwpid == tid)
    return elfcore_maybe_make_sect (abfd, base, sect);

  return TRUE;
}