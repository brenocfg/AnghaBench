#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {int sign_extend_vma; } ;

/* Variables and functions */
 scalar_t__ CONST_STRNEQ (char*,char*) ; 
 int /*<<< orphan*/  bfd_error_wrong_format ; 
 scalar_t__ bfd_get_flavour (int /*<<< orphan*/ *) ; 
 char* bfd_get_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_target_elf_flavour ; 
 TYPE_1__* get_elf_backend_data (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 

int
bfd_get_sign_extend_vma (bfd *abfd)
{
  char *name;

  if (bfd_get_flavour (abfd) == bfd_target_elf_flavour)
    return get_elf_backend_data (abfd)->sign_extend_vma;

  name = bfd_get_target (abfd);

  /* Return a proper value for DJGPP & PE COFF.
     This function is required for DWARF2 support, but there is
     no place to store this information in the COFF back end.
     Should enough other COFF targets add support for DWARF2,
     a place will have to be found.  Until then, this hack will do.  */
  if (CONST_STRNEQ (name, "coff-go32")
      || strcmp (name, "pe-i386") == 0
      || strcmp (name, "pei-i386") == 0
      || strcmp (name, "pe-arm-wince-little") == 0
      || strcmp (name, "pei-arm-wince-little") == 0)
    return 1;

  bfd_set_error (bfd_error_wrong_format);
  return -1;
}