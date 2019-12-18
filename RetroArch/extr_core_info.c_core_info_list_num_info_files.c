#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t count; TYPE_1__* list; } ;
typedef  TYPE_2__ core_info_list_t ;
typedef  int /*<<< orphan*/  config_file_t ;
struct TYPE_4__ {scalar_t__ config_data; } ;

/* Variables and functions */

size_t core_info_list_num_info_files(core_info_list_t *core_info_list)
{
   size_t i, num = 0;

   if (!core_info_list)
      return 0;

   for (i = 0; i < core_info_list->count; i++)
   {
      config_file_t *conf = (config_file_t*)
         core_info_list->list[i].config_data;
      num += !!conf;
   }

   return num;
}