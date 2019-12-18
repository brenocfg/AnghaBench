#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_4__ {int e_machine; } ;
struct TYPE_3__ {int elf_machine_code; int elf_machine_alt1; int elf_machine_alt2; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ bfd_get_flavour (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_target_elf_flavour ; 
 TYPE_2__* elf_elfheader (int /*<<< orphan*/ *) ; 
 TYPE_1__* get_elf_backend_data (int /*<<< orphan*/ *) ; 

bfd_boolean
bfd_alt_mach_code (bfd *abfd, int alternative)
{
  if (bfd_get_flavour (abfd) == bfd_target_elf_flavour)
    {
      int code;

      switch (alternative)
	{
	case 0:
	  code = get_elf_backend_data (abfd)->elf_machine_code;
	  break;

	case 1:
	  code = get_elf_backend_data (abfd)->elf_machine_alt1;
	  if (code == 0)
	    return FALSE;
	  break;

	case 2:
	  code = get_elf_backend_data (abfd)->elf_machine_alt2;
	  if (code == 0)
	    return FALSE;
	  break;

	default:
	  return FALSE;
	}

      elf_elfheader (abfd)->e_machine = code;

      return TRUE;
    }

  return FALSE;
}