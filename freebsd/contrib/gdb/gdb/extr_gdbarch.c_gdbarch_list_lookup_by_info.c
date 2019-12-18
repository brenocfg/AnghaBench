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
struct gdbarch_list {TYPE_1__* gdbarch; struct gdbarch_list* next; } ;
struct gdbarch_info {scalar_t__ bfd_arch_info; scalar_t__ byte_order; scalar_t__ osabi; } ;
struct TYPE_2__ {scalar_t__ bfd_arch_info; scalar_t__ byte_order; scalar_t__ osabi; } ;

/* Variables and functions */

struct gdbarch_list *
gdbarch_list_lookup_by_info (struct gdbarch_list *arches,
                             const struct gdbarch_info *info)
{
  for (; arches != NULL; arches = arches->next)
    {
      if (info->bfd_arch_info != arches->gdbarch->bfd_arch_info)
	continue;
      if (info->byte_order != arches->gdbarch->byte_order)
	continue;
      if (info->osabi != arches->gdbarch->osabi)
	continue;
      return arches;
    }
  return NULL;
}