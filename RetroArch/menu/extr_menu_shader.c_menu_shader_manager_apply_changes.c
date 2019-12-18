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
typedef  enum rarch_shader_type { ____Placeholder_rarch_shader_type } rarch_shader_type ;

/* Variables and functions */
 int RARCH_SHADER_NONE ; 
 int menu_shader_manager_get_type (struct video_shader*) ; 
 int /*<<< orphan*/  menu_shader_manager_save_preset (struct video_shader*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  menu_shader_manager_set_preset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 

void menu_shader_manager_apply_changes(struct video_shader *shader)
{
   enum rarch_shader_type type = RARCH_SHADER_NONE;

   if (!shader)
      return;

   type = menu_shader_manager_get_type(shader);

   if (shader->passes && type != RARCH_SHADER_NONE)
   {
      menu_shader_manager_save_preset(shader, NULL, true);
      return;
   }

   menu_shader_manager_set_preset(NULL, type, NULL, true);
}