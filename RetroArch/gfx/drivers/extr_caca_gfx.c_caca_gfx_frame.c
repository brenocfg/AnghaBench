#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ menu_is_alive; } ;
typedef  TYPE_1__ video_frame_info_t ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  caca_clear_canvas (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  caca_cv ; 
 int /*<<< orphan*/  caca_display ; 
 int /*<<< orphan*/  caca_dither ; 
 int /*<<< orphan*/  caca_dither_bitmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ,void const*) ; 
 void* caca_export_canvas_to_memory (int /*<<< orphan*/ ,char*,size_t*) ; 
 unsigned int caca_get_canvas_height (int /*<<< orphan*/ ) ; 
 unsigned int caca_get_canvas_width (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  caca_gfx_create () ; 
 int /*<<< orphan*/  caca_gfx_free (int /*<<< orphan*/ *) ; 
 void* caca_menu_frame ; 
 int /*<<< orphan*/  caca_refresh_display (int /*<<< orphan*/ ) ; 
 unsigned int caca_video_height ; 
 unsigned int caca_video_pitch ; 
 unsigned int caca_video_width ; 
 int /*<<< orphan*/  font_driver_render_msg (TYPE_1__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  menu_driver_frame (TYPE_1__*) ; 

__attribute__((used)) static bool caca_gfx_frame(void *data, const void *frame,
      unsigned frame_width, unsigned frame_height, uint64_t frame_count,
      unsigned pitch, const char *msg, video_frame_info_t *video_info)
{
   size_t len = 0;
   void *buffer = NULL;
   const void *frame_to_copy = frame;
   unsigned width = 0;
   unsigned height = 0;
   bool draw = true;

   (void)data;
   (void)frame;
   (void)frame_width;
   (void)frame_height;
   (void)pitch;
   (void)msg;

   if (!frame || !frame_width || !frame_height)
      return true;

   if (  caca_video_width  != frame_width   ||
         caca_video_height != frame_height  ||
         caca_video_pitch  != pitch)
   {
      if (frame_width > 4 && frame_height > 4)
      {
         caca_video_width = frame_width;
         caca_video_height = frame_height;
         caca_video_pitch = pitch;
         caca_gfx_free(NULL);
         caca_gfx_create();
      }
   }

   if (!caca_cv)
      return true;

   if (caca_menu_frame && video_info->menu_is_alive)
      frame_to_copy = caca_menu_frame;

   width = caca_get_canvas_width(caca_cv);
   height = caca_get_canvas_height(caca_cv);

   if (  frame_to_copy == frame &&
         frame_width   == 4 &&
         frame_height  == 4 &&
         (frame_width < width && frame_height < height))
      draw = false;

   if (video_info->menu_is_alive)
      draw = false;

   caca_clear_canvas(caca_cv);

#ifdef HAVE_MENU
   menu_driver_frame(video_info);
#endif

   if (msg)
      font_driver_render_msg(video_info, NULL, msg, NULL);

   if (draw)
   {
      caca_dither_bitmap(caca_cv, 0, 0,
            width,
            height,
            caca_dither, frame_to_copy);

      buffer = caca_export_canvas_to_memory(caca_cv, "caca", &len);

      if (buffer)
      {
         if (len)
            caca_refresh_display(caca_display);

         free(buffer);
      }
   }

   return true;
}