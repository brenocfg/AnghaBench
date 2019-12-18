#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct retro_system_timing {int sample_rate; int /*<<< orphan*/  fps; } ;
struct retro_game_geometry {double aspect_ratio; int max_width; int max_height; scalar_t__ base_height; scalar_t__ base_width; } ;
struct TYPE_5__ {int x; int y; scalar_t__ h; scalar_t__ w; } ;
struct TYPE_8__ {TYPE_1__ viewport; } ;
struct TYPE_7__ {scalar_t__ ntsc; } ;
struct TYPE_6__ {struct retro_system_timing timing; struct retro_game_geometry geometry; } ;

/* Variables and functions */
 scalar_t__ MD_NTSC_OUT_WIDTH (scalar_t__) ; 
 scalar_t__ SMS_NTSC_OUT_WIDTH (scalar_t__) ; 
 int SYSTEM_MCD ; 
 int SYSTEM_MD ; 
 int SYSTEM_PBC ; 
 TYPE_4__ bitmap ; 
 TYPE_3__ config ; 
 TYPE_2__ g_av_info ; 
 int /*<<< orphan*/  ntsc_fps ; 
 int /*<<< orphan*/  pal_fps ; 
 int /*<<< orphan*/  retro_reset () ; 
 int /*<<< orphan*/  system_frame_gen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  system_frame_sms (int /*<<< orphan*/ ) ; 
 int system_hw ; 
 scalar_t__ vdp_pal ; 
 scalar_t__ vheight ; 
 scalar_t__ vwidth ; 

__attribute__((used)) static void retro_set_viewport_dimensions(void)
{
   unsigned i;
   struct retro_game_geometry geom;
   struct retro_system_timing timing;

   /* HACK: Emulate 10 dummy frames to figure out the real viewport dimensions of the game. */
   if((system_hw & SYSTEM_PBC) == SYSTEM_MD || (system_hw & SYSTEM_PBC) == SYSTEM_MCD)
      for (i = 0; i < 10; i++)
         system_frame_gen(0);
   else
      for (i = 0; i < 10; i++)
         system_frame_sms(0);

   vwidth  = bitmap.viewport.w + (bitmap.viewport.x * 2);
   vheight = bitmap.viewport.h + (bitmap.viewport.y * 2);
    
   retro_reset();

#if defined(USE_NTSC)
   if (config.ntsc)
   {
      if (system_hw & SYSTEM_MD)
         vwidth = MD_NTSC_OUT_WIDTH(vwidth);
      else
         vwidth = SMS_NTSC_OUT_WIDTH(vwidth);
   }
#endif

   geom.aspect_ratio = 4.0 / 3.0;
   geom.base_width = vwidth;
   geom.base_height = vheight;
   //geom.max_width = 1024;
   //geom.max_height = 512;
   geom.max_width = 720;
   geom.max_height = 576;

   //timing.sample_rate = 44100;
   timing.sample_rate = 48000;

   if (vdp_pal)
      timing.fps = pal_fps;
   else
      timing.fps = ntsc_fps;

   g_av_info.geometry = geom;
   g_av_info.timing   = timing;
}