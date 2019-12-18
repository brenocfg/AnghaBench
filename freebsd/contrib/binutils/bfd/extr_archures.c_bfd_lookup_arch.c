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
struct TYPE_4__ {int arch; unsigned long mach; scalar_t__ the_default; struct TYPE_4__* next; } ;
typedef  TYPE_1__ bfd_arch_info_type ;

/* Variables and functions */
 TYPE_1__** bfd_archures_list ; 

const bfd_arch_info_type *
bfd_lookup_arch (enum bfd_architecture arch, unsigned long machine)
{
  const bfd_arch_info_type * const *app, *ap;

  for (app = bfd_archures_list; *app != NULL; app++)
    {
      for (ap = *app; ap != NULL; ap = ap->next)
	{
	  if (ap->arch == arch
	      && (ap->mach == machine
		  || (machine == 0 && ap->the_default)))
	    return ap;
	}
    }

  return NULL;
}