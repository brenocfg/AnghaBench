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
struct video_shader_parameter {int /*<<< orphan*/  maximum; int /*<<< orphan*/  current; int /*<<< orphan*/  minimum; int /*<<< orphan*/  initial; } ;
struct video_shader {struct video_shader_parameter* parameters; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int menu_driver_shader_modified ; 

int menu_shader_manager_clear_parameter(struct video_shader *shader,
      unsigned i)
{
   struct video_shader_parameter *param = shader ?
      &shader->parameters[i] : NULL;

   if (!param)
      return 0;

   param->current = param->initial;
   param->current = MIN(MAX(param->minimum,
            param->current), param->maximum);

   menu_driver_shader_modified = true;

   return 0;
}