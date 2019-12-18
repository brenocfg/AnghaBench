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
struct video_shader_pass {int /*<<< orphan*/  filter; } ;
struct video_shader {struct video_shader_pass* pass; } ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_FILTER_UNSPEC ; 
 int menu_driver_shader_modified ; 

int menu_shader_manager_clear_pass_filter(struct video_shader *shader,
      unsigned i)
{
   struct video_shader_pass *shader_pass = shader ?
      &shader->pass[i] : NULL;

   if (!shader_pass)
      return -1;

   shader_pass->filter = RARCH_FILTER_UNSPEC;

   menu_driver_shader_modified = true;

   return 0;
}