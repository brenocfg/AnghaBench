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
struct TYPE_7__ {int /*<<< orphan*/  id; } ;
struct TYPE_8__ {TYPE_1__ current; } ;
struct TYPE_9__ {int pal_enable; int pal60_enable; TYPE_2__ resolutions; } ;
struct TYPE_10__ {TYPE_3__ screen; } ;
struct TYPE_11__ {TYPE_4__ console; } ;
typedef  TYPE_5__ global_t ;

/* Variables and functions */
 int /*<<< orphan*/  gfx_ctx_ps3_get_resolution (int /*<<< orphan*/ ,unsigned int*,unsigned int*) ; 
 TYPE_5__* global_get_ptr () ; 

__attribute__((used)) static void gfx_ctx_ps3_get_video_output_size(void *data,
      unsigned *width, unsigned *height)
{
   global_t *global = global_get_ptr();

   if (!global)
      return;

   gfx_ctx_ps3_get_resolution(global->console.screen.resolutions.current.id,
         width, height);

   if (*width == 720 && *height == 576)
   {
      if (global->console.screen.pal_enable)
         global->console.screen.pal60_enable = true;
   }
   else
   {
      global->console.screen.pal_enable = false;
      global->console.screen.pal60_enable = false;
   }
}