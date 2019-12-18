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
struct video_shader {int dummy; } ;

/* Variables and functions */
 int menu_shader_manager_save_preset_internal (struct video_shader const*,char const*,int,int) ; 

bool menu_shader_manager_save_preset(const struct video_shader *shader,
      const char *basename, bool apply)
{
   return menu_shader_manager_save_preset_internal(
         shader, basename, apply, false);
}