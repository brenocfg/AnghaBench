#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__* data; } ;
typedef  TYPE_3__ math_matrix_4x4 ;
struct TYPE_8__ {size_t active_idx; size_t current_idx; scalar_t__** current_mat_data_pointer; scalar_t__* current_mat_data; TYPE_2__* uniforms; TYPE_1__* shader; } ;
typedef  TYPE_4__ glsl_shader_data_t ;
struct TYPE_6__ {int mvp; } ;
struct TYPE_5__ {int /*<<< orphan*/  modern; } ;

/* Variables and functions */
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  glUniformMatrix4fv (int,int,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static bool gl_glsl_set_mvp(void *shader_data, const void *mat_data)
{
   int loc;
   glsl_shader_data_t *glsl   = (glsl_shader_data_t*)shader_data;

   if (!glsl || !glsl->shader->modern)
      return false;

   loc = glsl->uniforms[glsl->active_idx].mvp;
   if (loc >= 0)
   {
      const math_matrix_4x4 *mat = (const math_matrix_4x4*)mat_data;

      if (  (glsl->current_idx != glsl->active_idx) ||
            (mat->data  != glsl->current_mat_data_pointer[glsl->active_idx]) ||
            (*mat->data != glsl->current_mat_data[glsl->active_idx]))
      {
         glUniformMatrix4fv(loc, 1, GL_FALSE, mat->data);
         glsl->current_idx                                = glsl->active_idx;
         glsl->current_mat_data_pointer[glsl->active_idx] = (float*)mat->data;
         glsl->current_mat_data[glsl->active_idx]         = *mat->data;
      }
   }

   return true;
}