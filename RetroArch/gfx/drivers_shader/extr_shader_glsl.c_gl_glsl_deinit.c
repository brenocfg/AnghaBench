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
typedef  int /*<<< orphan*/  glsl_shader_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gl_glsl_destroy_resources (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gl_glsl_deinit(void *data)
{
   glsl_shader_data_t *glsl = (glsl_shader_data_t*)data;

   if (!glsl)
      return;

   gl_glsl_destroy_resources(glsl);

   free(glsl);
}