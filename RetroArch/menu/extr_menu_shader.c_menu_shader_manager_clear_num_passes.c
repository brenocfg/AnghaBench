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
struct video_shader {scalar_t__ passes; } ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_ENTRIES_CTL_SET_REFRESH ; 
 int menu_driver_shader_modified ; 
 int /*<<< orphan*/  menu_entries_ctl (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  video_shader_resolve_parameters (int /*<<< orphan*/ *,struct video_shader*) ; 

int menu_shader_manager_clear_num_passes(struct video_shader *shader)
{
   bool refresh                = false;

   if (!shader)
      return 0;

   shader->passes = 0;

#ifdef HAVE_MENU
   menu_entries_ctl(MENU_ENTRIES_CTL_SET_REFRESH, &refresh);
#endif

   video_shader_resolve_parameters(NULL, shader);

   menu_driver_shader_modified = true;

   return 0;
}