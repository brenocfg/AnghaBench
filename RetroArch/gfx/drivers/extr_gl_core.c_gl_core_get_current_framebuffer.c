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
struct TYPE_2__ {uintptr_t hw_render_fbo; int /*<<< orphan*/  hw_render_enable; } ;
typedef  TYPE_1__ gl_core_t ;

/* Variables and functions */

__attribute__((used)) static uintptr_t gl_core_get_current_framebuffer(void *data)
{
   gl_core_t *gl = (gl_core_t*)data;
   if (!gl || !gl->hw_render_enable)
      return 0;
   return gl->hw_render_fbo;
}