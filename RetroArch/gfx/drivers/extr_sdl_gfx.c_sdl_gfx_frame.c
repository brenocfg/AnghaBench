#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_frame_info_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  title ;
struct TYPE_11__ {int /*<<< orphan*/  frame; scalar_t__ active; } ;
struct TYPE_13__ {int /*<<< orphan*/  in_fmt; } ;
struct TYPE_12__ {TYPE_5__* screen; TYPE_1__ menu; TYPE_3__ scaler; } ;
typedef  TYPE_2__ sdl_video_t ;
struct TYPE_14__ {int /*<<< orphan*/  format; int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  pitch; int /*<<< orphan*/  pixels; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_BlitSurface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDL_Flip (TYPE_5__*) ; 
 int /*<<< orphan*/  SDL_LockSurface (TYPE_5__*) ; 
 scalar_t__ SDL_MUSTLOCK (TYPE_5__*) ; 
 int /*<<< orphan*/  SDL_UnlockSurface (TYPE_5__*) ; 
 int /*<<< orphan*/  SDL_WM_SetCaption (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  menu_driver_frame (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdl_render_msg (TYPE_2__*,TYPE_5__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_driver_get_window_title (char*,int) ; 
 int /*<<< orphan*/  video_frame_scale (TYPE_3__*,int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static bool sdl_gfx_frame(void *data, const void *frame, unsigned width,
      unsigned height, uint64_t frame_count,
      unsigned pitch, const char *msg, video_frame_info_t *video_info)
{
   sdl_video_t                    *vid = (sdl_video_t*)data;
   char title[128];

   if (!frame)
      return true;

   title[0] = '\0';

   video_driver_get_window_title(title, sizeof(title));

   if (SDL_MUSTLOCK(vid->screen))
      SDL_LockSurface(vid->screen);

   video_frame_scale(
         &vid->scaler,
         vid->screen->pixels,
         frame,
         vid->scaler.in_fmt,
         vid->screen->w,
         vid->screen->h,
         vid->screen->pitch,
         width,
         height,
         pitch);

#ifdef HAVE_MENU
   menu_driver_frame(video_info);
#endif

   if (vid->menu.active)
      SDL_BlitSurface(vid->menu.frame, NULL, vid->screen, NULL);

   if (msg)
      sdl_render_msg(vid, vid->screen,
            msg, vid->screen->w, vid->screen->h, vid->screen->format);

   if (SDL_MUSTLOCK(vid->screen))
      SDL_UnlockSurface(vid->screen);

   if (title[0])
      SDL_WM_SetCaption(title, NULL);

   SDL_Flip(vid->screen);

   return true;
}