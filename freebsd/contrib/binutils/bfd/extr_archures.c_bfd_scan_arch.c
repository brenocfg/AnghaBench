#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ (* scan ) (TYPE_1__ const*,char const*) ;struct TYPE_5__* next; } ;
typedef  TYPE_1__ bfd_arch_info_type ;

/* Variables and functions */
 TYPE_1__** bfd_archures_list ; 
 scalar_t__ stub1 (TYPE_1__ const*,char const*) ; 

const bfd_arch_info_type *
bfd_scan_arch (const char *string)
{
  const bfd_arch_info_type * const *app, *ap;

  /* Look through all the installed architectures.  */
  for (app = bfd_archures_list; *app != NULL; app++)
    {
      for (ap = *app; ap != NULL; ap = ap->next)
	{
	  if (ap->scan (ap, string))
	    return ap;
	}
    }

  return NULL;
}