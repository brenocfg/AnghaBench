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
struct TYPE_5__ {void* core_pid; void* core_signal; } ;
struct TYPE_4__ {int namesz; int descsz; scalar_t__ descpos; scalar_t__ descdata; int /*<<< orphan*/  namedata; } ;
typedef  TYPE_1__ Elf_Internal_Note ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  _bfd_elfcore_make_pseudosection (int /*<<< orphan*/ *,char*,size_t,scalar_t__) ; 
 void* bfd_get_16 (int /*<<< orphan*/ *,scalar_t__) ; 
 void* bfd_get_32 (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_2__* elf_tdata (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bfd_boolean
elf_i386_grok_prstatus (bfd *abfd, Elf_Internal_Note *note)
{
  int offset;
  size_t size;

  if (note->namesz == 8 && strcmp (note->namedata, "FreeBSD") == 0)
    {
      int pr_version = bfd_get_32 (abfd, note->descdata);

      if (pr_version != 1)
 	return FALSE;

      /* pr_cursig */
      elf_tdata (abfd)->core_signal = bfd_get_32 (abfd, note->descdata + 20);

      /* pr_pid */
      elf_tdata (abfd)->core_pid = bfd_get_32 (abfd, note->descdata + 24);

      /* pr_reg */
      offset = 28;
      size = bfd_get_32 (abfd, note->descdata + 8);
    }
  else
    {
      switch (note->descsz)
	{
	default:
	  return FALSE;

	case 144:		/* Linux/i386 */
	  /* pr_cursig */
	  elf_tdata (abfd)->core_signal = bfd_get_16 (abfd, note->descdata + 12);

	  /* pr_pid */
	  elf_tdata (abfd)->core_pid = bfd_get_32 (abfd, note->descdata + 24);

	  /* pr_reg */
	  offset = 72;
	  size = 68;

	  break;
	}
    }

  /* Make a ".reg/999" section.  */
  return _bfd_elfcore_make_pseudosection (abfd, ".reg",
					  size, note->descpos + offset);
}