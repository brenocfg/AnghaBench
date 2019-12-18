#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  enum bfd_architecture { ____Placeholder_bfd_architecture } bfd_architecture ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_4__ {int /*<<< orphan*/ * arch_info; } ;
typedef  TYPE_1__ bfd ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int bfd_arch_unknown ; 
 int /*<<< orphan*/  bfd_default_arch_struct ; 
 int /*<<< orphan*/  bfd_default_set_arch_mach (TYPE_1__*,int,unsigned long) ; 

__attribute__((used)) static bfd_boolean
srec_set_arch_mach (bfd *abfd, enum bfd_architecture arch, unsigned long mach)
{
  if (arch != bfd_arch_unknown)
    return bfd_default_set_arch_mach (abfd, arch, mach);

  abfd->arch_info = & bfd_default_arch_struct;
  return TRUE;
}