#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  irix_compat_t ;
struct TYPE_3__ {int /*<<< orphan*/ * xvec; } ;
typedef  TYPE_1__ bfd ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_elf32_nbigmips_vec ; 
 int /*<<< orphan*/  bfd_elf32_nlittlemips_vec ; 
 int /*<<< orphan*/  ict_irix6 ; 
 int /*<<< orphan*/  ict_none ; 

__attribute__((used)) static irix_compat_t
elf_n32_mips_irix_compat (bfd *abfd)
{
  if ((abfd->xvec == &bfd_elf32_nbigmips_vec)
      || (abfd->xvec == &bfd_elf32_nlittlemips_vec))
    return ict_irix6;
  else
    return ict_none;
}