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
typedef  int /*<<< orphan*/  gl_core_t ;

/* Variables and functions */
 int /*<<< orphan*/  font_driver_free_osd () ; 
 int /*<<< orphan*/  gl_core_context_bind_hw_render (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gl_core_destroy_resources (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_context_driver_free () ; 

__attribute__((used)) static void gl_core_free(void *data)
{
   gl_core_t *gl = (gl_core_t*)data;
   if (!gl)
      return;

   gl_core_context_bind_hw_render(gl, false);
   font_driver_free_osd();
   gl_core_destroy_resources(gl);
   video_context_driver_free();
}