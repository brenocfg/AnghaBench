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
struct TYPE_2__ {int keep_aspect; int should_resize; } ;
typedef  TYPE_1__ gl_core_t ;

/* Variables and functions */

__attribute__((used)) static void gl_core_set_aspect_ratio(void *data, unsigned aspect_ratio_idx)
{
   gl_core_t *gl = (gl_core_t*)data;

   if (!gl)
      return;

   gl->keep_aspect   = true;
   gl->should_resize = true;
}