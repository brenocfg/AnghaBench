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
struct TYPE_5__ {int core_signal; int core_pid; } ;
struct TYPE_4__ {int descsz; scalar_t__ descpos; scalar_t__ descdata; } ;
typedef  TYPE_1__ Elf_Internal_Note ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  _bfd_elfcore_make_pseudosection (int /*<<< orphan*/ *,char*,size_t,scalar_t__) ; 
 int bfd_get_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int bfd_get_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* elf_tdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bfd_boolean
elf32_arm_nabi_grok_prstatus (bfd *abfd, Elf_Internal_Note *note)
{
  int offset;
  size_t size;

  switch (note->descsz)
    {
      default:
	return FALSE;

      case 148:		/* Linux/ARM 32-bit*/
	/* pr_cursig */
	elf_tdata (abfd)->core_signal = bfd_get_16 (abfd, note->descdata + 12);

	/* pr_pid */
	elf_tdata (abfd)->core_pid = bfd_get_32 (abfd, note->descdata + 24);

	/* pr_reg */
	offset = 72;
	size = 72;

	break;

      case 96:		/* FreeBSD/ARM */
	/* pr_cursig */
	if (elf_tdata(abfd)->core_signal == 0)
	  elf_tdata (abfd)->core_signal = ((int *)(note->descdata))[5];

	/* pr_pid */
	elf_tdata (abfd)->core_pid = ((int *)(note->descdata))[6];

	/* pr_reg */
	offset = 28;
	size = 68;
	break;
    }

  /* Make a ".reg/999" section.  */
  return _bfd_elfcore_make_pseudosection (abfd, ".reg",
					  size, note->descpos + offset);
}