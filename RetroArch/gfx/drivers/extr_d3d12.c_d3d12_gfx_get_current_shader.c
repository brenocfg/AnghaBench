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
struct TYPE_2__ {struct video_shader* shader_preset; } ;
typedef  TYPE_1__ d3d12_video_t ;

/* Variables and functions */

__attribute__((used)) static struct video_shader* d3d12_gfx_get_current_shader(void* data)
{
   d3d12_video_t* d3d12 = (d3d12_video_t*)data;

   if (!d3d12)
      return NULL;

   return d3d12->shader_preset;
}