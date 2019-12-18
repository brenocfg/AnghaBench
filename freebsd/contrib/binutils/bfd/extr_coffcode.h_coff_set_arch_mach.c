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
typedef  enum bfd_architecture { ____Placeholder_bfd_architecture } bfd_architecture ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int bfd_arch_unknown ; 
 int /*<<< orphan*/  bfd_default_set_arch_mach (int /*<<< orphan*/ *,int,unsigned long) ; 
 int /*<<< orphan*/  coff_set_flags (int /*<<< orphan*/ *,unsigned int*,unsigned short*) ; 

__attribute__((used)) static bfd_boolean
coff_set_arch_mach (bfd * abfd,
		    enum bfd_architecture arch,
		    unsigned long machine)
{
  unsigned dummy1;
  unsigned short dummy2;

  if (! bfd_default_set_arch_mach (abfd, arch, machine))
    return FALSE;

  if (arch != bfd_arch_unknown
      && ! coff_set_flags (abfd, &dummy1, &dummy2))
    return FALSE;		/* We can't represent this type.  */

  return TRUE;			/* We're easy...  */
}