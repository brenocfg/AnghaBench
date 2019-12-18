#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* xvec; } ;
typedef  TYPE_2__ bfd ;
struct TYPE_8__ {int e_phnum; } ;
struct TYPE_6__ {scalar_t__ flavour; } ;
typedef  int /*<<< orphan*/  Elf_Internal_Phdr ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_error_wrong_format ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_target_elf_flavour ; 
 TYPE_3__* elf_elfheader (TYPE_2__*) ; 

long
bfd_get_elf_phdr_upper_bound (bfd *abfd)
{
  if (abfd->xvec->flavour != bfd_target_elf_flavour)
    {
      bfd_set_error (bfd_error_wrong_format);
      return -1;
    }

  return elf_elfheader (abfd)->e_phnum * sizeof (Elf_Internal_Phdr);
}