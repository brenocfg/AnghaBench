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
struct TYPE_4__ {int /*<<< orphan*/  system; } ;
struct TYPE_5__ {TYPE_1__ directory; int /*<<< orphan*/  path; } ;
typedef  TYPE_2__ core_info_ctx_firmware_t ;

/* Variables and functions */
 int /*<<< orphan*/  core_info_curr_list ; 
 int core_info_list_update_missing_firmware_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

bool core_info_list_update_missing_firmware(core_info_ctx_firmware_t *info,
      bool *set_missing_bios)
{
   if (!info)
      return false;
   return core_info_list_update_missing_firmware_internal(
         core_info_curr_list,
         info->path, info->directory.system,
         set_missing_bios);
}