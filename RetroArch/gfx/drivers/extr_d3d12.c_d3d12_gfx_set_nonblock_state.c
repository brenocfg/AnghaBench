#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int vsync; } ;
struct TYPE_4__ {TYPE_1__ chain; } ;
typedef  TYPE_2__ d3d12_video_t ;

/* Variables and functions */

__attribute__((used)) static void d3d12_gfx_set_nonblock_state(void* data, bool toggle)
{
   d3d12_video_t* d3d12 = (d3d12_video_t*)data;
   d3d12->chain.vsync   = !toggle;
}