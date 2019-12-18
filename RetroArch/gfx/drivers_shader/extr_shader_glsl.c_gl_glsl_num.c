#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* shader; } ;
typedef  TYPE_2__ glsl_shader_data_t ;
struct TYPE_3__ {int passes; } ;

/* Variables and functions */

__attribute__((used)) static unsigned gl_glsl_num(void *data)
{
   glsl_shader_data_t *glsl = (glsl_shader_data_t*)data;
   if (glsl && glsl->shader)
      return glsl->shader->passes;
   return 0;
}