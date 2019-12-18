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
struct TYPE_3__ {scalar_t__ full_width; scalar_t__ full_height; } ;
struct TYPE_4__ {TYPE_1__ vp; scalar_t__ resize_chain; } ;
typedef  TYPE_2__ d3d12_video_t ;

/* Variables and functions */
 int /*<<< orphan*/  video_driver_set_size (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  win32_check_window (int*,scalar_t__*,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static bool d3d12_gfx_alive(void* data)
{
   bool           quit;
   d3d12_video_t* d3d12 = (d3d12_video_t*)data;

   win32_check_window(&quit, &d3d12->resize_chain, &d3d12->vp.full_width, &d3d12->vp.full_height);

   if (d3d12->resize_chain && d3d12->vp.full_width != 0 && d3d12->vp.full_height != 0)
      video_driver_set_size(&d3d12->vp.full_width, &d3d12->vp.full_height);

   return !quit;
}