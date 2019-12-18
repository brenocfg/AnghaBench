#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct video_shader {int dummy; } ;
struct TYPE_2__ {struct video_shader* shader; } ;
typedef  TYPE_1__ glsl_shader_data_t ;

/* Variables and functions */

__attribute__((used)) static struct video_shader *gl_glsl_get_current_shader(void *data)
{
   glsl_shader_data_t *glsl = (glsl_shader_data_t*)data;
   if (!glsl)
      return NULL;
   return glsl->shader;
}