#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_5__ {int flags; } ;
typedef  TYPE_1__ asection ;
struct TYPE_6__ {int /*<<< orphan*/  e_machine; } ;
typedef  TYPE_2__ Elf_Internal_Ehdr ;

/* Variables and functions */
 int SEC_RELOC ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_error_wrong_format ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 TYPE_2__* elf_elfheader (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
check_for_relocs (bfd * abfd, asection * o, void * failed)
{
  if ((o->flags & SEC_RELOC) != 0)
    {
      Elf_Internal_Ehdr *ehdrp;

      ehdrp = elf_elfheader (abfd);
      _bfd_error_handler (_("%B: Relocations in generic ELF (EM: %d)"),
			  abfd, ehdrp->e_machine);

      bfd_set_error (bfd_error_wrong_format);
      * (bfd_boolean *) failed = TRUE;
    }
}