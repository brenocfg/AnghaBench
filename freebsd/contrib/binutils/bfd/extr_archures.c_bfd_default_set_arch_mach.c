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
typedef  enum bfd_architecture { ____Placeholder_bfd_architecture } bfd_architecture ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_3__ {int /*<<< orphan*/ * arch_info; } ;
typedef  TYPE_1__ bfd ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bfd_default_arch_struct ; 
 int /*<<< orphan*/  bfd_error_bad_value ; 
 int /*<<< orphan*/ * bfd_lookup_arch (int,unsigned long) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 

bfd_boolean
bfd_default_set_arch_mach (bfd *abfd,
			   enum bfd_architecture arch,
			   unsigned long mach)
{
  abfd->arch_info = bfd_lookup_arch (arch, mach);
  if (abfd->arch_info != NULL)
    return TRUE;

  abfd->arch_info = &bfd_default_arch_struct;
  bfd_set_error (bfd_error_bad_value);
  return FALSE;
}