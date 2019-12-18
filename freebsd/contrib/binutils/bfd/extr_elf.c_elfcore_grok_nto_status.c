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
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_7__ {int alignment_power; int /*<<< orphan*/  filepos; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ asection ;
struct TYPE_9__ {short core_signal; long core_lwpid; void* core_pid; } ;
struct TYPE_8__ {int /*<<< orphan*/  descpos; int /*<<< orphan*/  descsz; void* descdata; } ;
typedef  TYPE_2__ Elf_Internal_Note ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SEC_HAS_CONTENTS ; 
 char* bfd_alloc (int /*<<< orphan*/ *,scalar_t__) ; 
 short bfd_get_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* bfd_get_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* bfd_make_section_anyway_with_flags (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 TYPE_5__* elf_tdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elfcore_maybe_make_sect (int /*<<< orphan*/ *,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,long) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static bfd_boolean
elfcore_grok_nto_status (bfd *abfd, Elf_Internal_Note *note, long *tid)
{
  void *ddata = note->descdata;
  char buf[100];
  char *name;
  asection *sect;
  short sig;
  unsigned flags;

  /* nto_procfs_status 'pid' field is at offset 0.  */
  elf_tdata (abfd)->core_pid = bfd_get_32 (abfd, (bfd_byte *) ddata);

  /* nto_procfs_status 'tid' field is at offset 4.  Pass it back.  */
  *tid = bfd_get_32 (abfd, (bfd_byte *) ddata + 4);

  /* nto_procfs_status 'flags' field is at offset 8.  */
  flags = bfd_get_32 (abfd, (bfd_byte *) ddata + 8);

  /* nto_procfs_status 'what' field is at offset 14.  */
  if ((sig = bfd_get_16 (abfd, (bfd_byte *) ddata + 14)) > 0)
    {
      elf_tdata (abfd)->core_signal = sig;
      elf_tdata (abfd)->core_lwpid = *tid;
    }

  /* _DEBUG_FLAG_CURTID (current thread) is 0x80.  Some cores
     do not come from signals so we make sure we set the current
     thread just in case.  */
  if (flags & 0x00000080)
    elf_tdata (abfd)->core_lwpid = *tid;

  /* Make a ".qnx_core_status/%d" section.  */
  sprintf (buf, ".qnx_core_status/%ld", *tid);

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

  return (elfcore_maybe_make_sect (abfd, ".qnx_core_status", sect));
}