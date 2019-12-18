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
struct TYPE_2__ {int vsync; } ;
typedef  TYPE_1__ d3d11_video_t ;

/* Variables and functions */

__attribute__((used)) static void d3d11_gfx_set_nonblock_state(void* data, bool toggle)
{
   d3d11_video_t* d3d11 = (d3d11_video_t*)data;

   if (!d3d11)
      return;

   d3d11->vsync = !toggle;
}