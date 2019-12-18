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
struct TYPE_2__ {int /*<<< orphan*/  filter_chain; } ;
typedef  TYPE_1__ gl_core_t ;

/* Variables and functions */
 struct video_shader* gl_core_filter_chain_get_preset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct video_shader *gl_core_get_current_shader(void *data)
{
   gl_core_t *gl = (gl_core_t*)data;
   if (!gl || !gl->filter_chain)
      return NULL;

   return gl_core_filter_chain_get_preset(gl->filter_chain);
}