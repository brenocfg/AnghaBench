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
struct TYPE_5__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ core_info_t ;
struct TYPE_6__ {int /*<<< orphan*/ * list; } ;
typedef  TYPE_2__ core_info_list_t ;

/* Variables and functions */

core_info_t *core_info_get(core_info_list_t *list, size_t i)
{
   core_info_t *info = NULL;

   if (!list)
      return NULL;
   info = (core_info_t*)&list->list[i];
   if (!info || !info->path)
      return NULL;

   return info;
}