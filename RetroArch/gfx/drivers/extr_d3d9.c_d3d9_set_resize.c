#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int width; unsigned int height; } ;
struct TYPE_5__ {TYPE_1__ video_info; } ;
typedef  TYPE_2__ d3d9_video_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_LOG (char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  video_driver_set_size (unsigned int*,unsigned int*) ; 

__attribute__((used)) static bool d3d9_set_resize(d3d9_video_t *d3d,
      unsigned new_width, unsigned new_height)
{
   /* No changes? */
   if (     (new_width  == d3d->video_info.width)
         && (new_height == d3d->video_info.height))
      return false;

   RARCH_LOG("[D3D9]: Resize %ux%u.\n", new_width, new_height);
   d3d->video_info.width  = new_width;
   d3d->video_info.height = new_height;
   video_driver_set_size(&new_width, &new_height);

   return true;
}