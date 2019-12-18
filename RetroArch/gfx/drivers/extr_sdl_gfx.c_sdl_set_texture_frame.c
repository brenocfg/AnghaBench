#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {TYPE_3__* frame; int /*<<< orphan*/  scaler; } ;
struct TYPE_5__ {TYPE_1__ menu; } ;
typedef  TYPE_2__ sdl_video_t ;
typedef  enum scaler_pix_fmt { ____Placeholder_scaler_pix_fmt } scaler_pix_fmt ;
struct TYPE_6__ {int /*<<< orphan*/  pitch; int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  pixels; } ;

/* Variables and functions */
 int SCALER_FMT_ARGB8888 ; 
 int SCALER_FMT_RGBA4444 ; 
 int /*<<< orphan*/  SDL_SRCALPHA ; 
 int /*<<< orphan*/  SDL_SetAlpha (TYPE_3__*,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  video_frame_scale (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static void sdl_set_texture_frame(void *data, const void *frame, bool rgb32,
      unsigned width, unsigned height, float alpha)
{
   enum scaler_pix_fmt format = rgb32
      ? SCALER_FMT_ARGB8888 : SCALER_FMT_RGBA4444;
   sdl_video_t           *vid = (sdl_video_t*)data;

   video_frame_scale(
         &vid->menu.scaler,
         vid->menu.frame->pixels,
         frame,
         format,
         vid->menu.frame->w,
         vid->menu.frame->h,
         vid->menu.frame->pitch,
         width,
         height,
         width * (rgb32 ? sizeof(uint32_t) : sizeof(uint16_t))
         );

   SDL_SetAlpha(vid->menu.frame, SDL_SRCALPHA, 255.0 * alpha);
}