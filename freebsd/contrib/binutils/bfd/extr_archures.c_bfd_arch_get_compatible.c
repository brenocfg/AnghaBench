#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ bfd_boolean ;
struct TYPE_10__ {scalar_t__ arch; TYPE_1__ const* (* compatible ) (TYPE_1__ const*,TYPE_1__ const*) ;} ;
typedef  TYPE_1__ bfd_arch_info_type ;
struct TYPE_11__ {TYPE_1__ const* arch_info; } ;
typedef  TYPE_2__ bfd ;

/* Variables and functions */
 scalar_t__ bfd_arch_unknown ; 
 int /*<<< orphan*/  bfd_get_target (TYPE_2__ const*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__ const* stub1 (TYPE_1__ const*,TYPE_1__ const*) ; 

const bfd_arch_info_type *
bfd_arch_get_compatible (const bfd *abfd,
			 const bfd *bbfd,
			 bfd_boolean accept_unknowns)
{
  const bfd * ubfd = NULL;

  /* Look for an unknown architecture.  */
  if (((ubfd = abfd) && ubfd->arch_info->arch == bfd_arch_unknown)
      || ((ubfd = bbfd) && ubfd->arch_info->arch == bfd_arch_unknown))
    {
      /* We can allow an unknown architecture if accept_unknowns
	 is true, or if the target is the "binary" format, which
	 has an unknown architecture.  Since the binary format can
	 only be set by explicit request from the user, it is safe
	 to assume that they know what they are doing.  */
      if (accept_unknowns
	  || strcmp (bfd_get_target (ubfd), "binary") == 0)
	return ubfd->arch_info;
      return NULL;
    }

  /* Otherwise architecture-specific code has to decide.  */
  return abfd->arch_info->compatible (abfd->arch_info, bbfd->arch_info);
}