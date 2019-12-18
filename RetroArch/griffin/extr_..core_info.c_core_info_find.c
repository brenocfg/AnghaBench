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
struct TYPE_3__ {int /*<<< orphan*/  inf; } ;
typedef  TYPE_1__ core_info_ctx_find_t ;

/* Variables and functions */
 int /*<<< orphan*/  core_info_curr_list ; 
 int /*<<< orphan*/  core_info_find_internal (int /*<<< orphan*/ ,char const*) ; 

bool core_info_find(core_info_ctx_find_t *info, const char *core_path)
{
   if (!info || !core_info_curr_list)
      return false;
   info->inf = core_info_find_internal(core_info_curr_list, core_path);
   if (!info->inf)
      return false;
   return true;
}