#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int quitting; int should_resize; } ;
typedef  TYPE_1__ d3d9_video_t ;

/* Variables and functions */
 int /*<<< orphan*/  d3d9_restore (TYPE_1__*) ; 
 int /*<<< orphan*/  d3d9_set_resize (TYPE_1__*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  video_driver_get_size (unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  video_driver_set_size (unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  win32_check_window (int*,int*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static bool d3d9_alive(void *data)
{
   unsigned temp_width   = 0;
   unsigned temp_height  = 0;
   bool ret              = false;
   bool        quit      = false;
   bool        resize    = false;
   d3d9_video_t *d3d     = (d3d9_video_t*)data;

   /* Needed because some context drivers don't track their sizes */
   video_driver_get_size(&temp_width, &temp_height);

#ifndef _XBOX
   win32_check_window(&quit, &resize, &temp_width, &temp_height);
#endif

   if (quit)
      d3d->quitting      = quit;

   if (resize)
   {
      d3d->should_resize = true;
      d3d9_set_resize(d3d, temp_width, temp_height);
      d3d9_restore(d3d);
   }

   ret = !quit;

   if (  temp_width  != 0 &&
         temp_height != 0)
      video_driver_set_size(&temp_width, &temp_height);

   return ret;
}