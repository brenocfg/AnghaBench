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
struct retro_system_info {char* library_name; char* library_version; int need_fullpath; char* valid_extensions; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct retro_system_info*,int /*<<< orphan*/ ,int) ; 

void libretro_dummy_retro_get_system_info(
      struct retro_system_info *info)
{
   memset(info, 0, sizeof(*info));
   info->library_name     = "";
   info->library_version  = "";
   info->need_fullpath    = false;
   info->valid_extensions = ""; /* Nothing. */
}