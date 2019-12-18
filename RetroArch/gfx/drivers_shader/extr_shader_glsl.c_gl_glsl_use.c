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
struct TYPE_5__ {unsigned int active_idx; TYPE_1__* prg; } ;
typedef  TYPE_2__ glsl_shader_data_t ;
struct TYPE_4__ {scalar_t__ id; } ;
typedef  scalar_t__ GLuint ;

/* Variables and functions */
 int /*<<< orphan*/  glUseProgram (scalar_t__) ; 
 int /*<<< orphan*/  gl_glsl_reset_attrib (TYPE_2__*) ; 

__attribute__((used)) static void gl_glsl_use(void *data, void *shader_data, unsigned idx, bool set_active)
{
   GLuint id;

   if (set_active)
   {
      glsl_shader_data_t *glsl = (glsl_shader_data_t*)shader_data;
      if (!glsl)
         return;

      gl_glsl_reset_attrib(glsl);
      glsl->active_idx        = idx;
      id                      = glsl->prg[idx].id;
   }
   else
      id = (GLuint)idx;

   glUseProgram(id);
}