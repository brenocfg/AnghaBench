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
struct TYPE_8__ {TYPE_2__* uniforms; TYPE_3__* shader; } ;
typedef  TYPE_4__ glsl_shader_data_t ;
struct TYPE_7__ {unsigned int passes; } ;
struct TYPE_6__ {TYPE_1__* prev; } ;
struct TYPE_5__ {scalar_t__ texture; } ;

/* Variables and functions */
 unsigned int MAX (unsigned int,unsigned int) ; 
 unsigned int PREV_TEXTURES ; 

__attribute__((used)) static unsigned gl_glsl_get_prev_textures(void *data)
{
   unsigned i, j;
   unsigned max_prev = 0;
   glsl_shader_data_t *glsl = (glsl_shader_data_t*)data;

   if (!glsl)
      return 0;

   for (i = 1; i <= glsl->shader->passes; i++)
      for (j = 0; j < PREV_TEXTURES; j++)
         if (glsl->uniforms[i].prev[j].texture >= 0)
            max_prev = MAX(j + 1, max_prev);

   return max_prev;
}