#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t id; } ;
struct TYPE_9__ {TYPE_4__ current; } ;
struct TYPE_7__ {TYPE_3__ resolutions; } ;
struct TYPE_8__ {TYPE_1__ screen; } ;
struct TYPE_11__ {TYPE_2__ console; } ;
typedef  TYPE_5__ global_t ;

/* Variables and functions */
 size_t GX_RESOLUTIONS_LAST ; 
 TYPE_5__* global_get_ptr () ; 
 unsigned int** menu_gx_resolutions ; 

__attribute__((used)) static void gx_get_video_output_size(void *data,
      unsigned *width, unsigned *height)
{
   global_t *global = global_get_ptr();

   (void)data;

   /* If the current index is out of bound default it to zero */
   if (global->console.screen.resolutions.current.id > GX_RESOLUTIONS_LAST)
      global->console.screen.resolutions.current.id = 0;

   *width  = menu_gx_resolutions[
      global->console.screen.resolutions.current.id][0];
   *height = menu_gx_resolutions[
      global->console.screen.resolutions.current.id][1];
}