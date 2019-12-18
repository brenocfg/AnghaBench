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
typedef  int bfd_boolean ;
struct TYPE_6__ {TYPE_1__* xvec; } ;
typedef  TYPE_2__ bfd ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_5__ {scalar_t__ flavour; } ;

/* Variables and functions */
 int TRUE ; 
 scalar_t__ bfd_target_elf_flavour ; 
 scalar_t__ elf_section_type (int /*<<< orphan*/  const*) ; 

bfd_boolean
_bfd_elf_match_sections_by_type (bfd *abfd, const asection *asec,
				 bfd *bbfd, const asection *bsec)
{
  if (asec == NULL
      || bsec == NULL
      || abfd->xvec->flavour != bfd_target_elf_flavour
      || bbfd->xvec->flavour != bfd_target_elf_flavour)
    return TRUE;

  return elf_section_type (asec) == elf_section_type (bsec);
}