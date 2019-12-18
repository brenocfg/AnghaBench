#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ bfd_arch_sparc ; 
 scalar_t__ bfd_get_arch (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_get_flavour (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_get_mach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_set_arch_mach (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ bfd_target_aout_flavour ; 

__attribute__((used)) static bfd_boolean
sunos_merge_private_bfd_data (bfd *ibfd, bfd *obfd)
{
  if (bfd_get_flavour (ibfd) != bfd_target_aout_flavour
      || bfd_get_flavour (obfd) != bfd_target_aout_flavour)
    return TRUE;

  if (bfd_get_arch (obfd) == bfd_arch_sparc)
    {
      if (bfd_get_mach (obfd) < bfd_get_mach (ibfd))
	bfd_set_arch_mach (obfd, bfd_arch_sparc, bfd_get_mach (ibfd));
    }

  return TRUE;
}