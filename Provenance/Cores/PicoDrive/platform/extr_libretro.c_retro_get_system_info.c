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
struct retro_system_info {char* library_name; char* valid_extensions; int need_fullpath; int /*<<< orphan*/  library_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERSION ; 
 int /*<<< orphan*/  memset (struct retro_system_info*,int /*<<< orphan*/ ,int) ; 

void retro_get_system_info(struct retro_system_info *info)
{
	memset(info, 0, sizeof(*info));
	info->library_name = "PicoDrive";
	info->library_version = VERSION;
	info->valid_extensions = "bin|gen|smd|md|32x|cue|iso|sms";
	info->need_fullpath = true;
}