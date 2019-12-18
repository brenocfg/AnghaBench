#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_6__* shader; } ;
typedef  TYPE_4__ glsl_shader_data_t ;
struct TYPE_11__ {unsigned int passes; TYPE_1__* pass; } ;
struct TYPE_8__ {TYPE_6__* fragment; TYPE_6__* vertex; } ;
struct TYPE_9__ {TYPE_2__ string; } ;
struct TYPE_7__ {TYPE_3__ source; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_6__*) ; 

__attribute__((used)) static void gl_glsl_deinit_shader(glsl_shader_data_t *glsl)
{
   unsigned i;

   if (!glsl || !glsl->shader)
      return;

   for (i = 0; i < glsl->shader->passes; i++)
   {
      free(glsl->shader->pass[i].source.string.vertex);
      free(glsl->shader->pass[i].source.string.fragment);
   }

   free(glsl->shader);
   glsl->shader = NULL;
}