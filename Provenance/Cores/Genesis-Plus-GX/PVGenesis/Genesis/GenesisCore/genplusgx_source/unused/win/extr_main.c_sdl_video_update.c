#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ w; scalar_t__ h; scalar_t__ y; scalar_t__ x; } ;
struct TYPE_9__ {scalar_t__ w; scalar_t__ h; scalar_t__ y; scalar_t__ x; } ;
struct TYPE_6__ {int changed; scalar_t__ w; int x; scalar_t__ h; int y; } ;
struct TYPE_8__ {TYPE_1__ viewport; } ;
struct TYPE_7__ {int /*<<< orphan*/  frames_rendered; int /*<<< orphan*/  surf_screen; TYPE_5__ drect; TYPE_4__ srect; int /*<<< orphan*/  surf_bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_BlitSurface (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  SDL_FillRect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_UpdateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ VIDEO_HEIGHT ; 
 scalar_t__ VIDEO_WIDTH ; 
 TYPE_3__ bitmap ; 
 TYPE_2__ sdl_video ; 
 int /*<<< orphan*/  system_frame (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdl_video_update()
{
  system_frame(0);

  /* viewport size changed */
  if(bitmap.viewport.changed & 1)
  {
    bitmap.viewport.changed &= ~1;

    /* source bitmap */
    sdl_video.srect.w = bitmap.viewport.w+2*bitmap.viewport.x;
    sdl_video.srect.h = bitmap.viewport.h+2*bitmap.viewport.y;
    sdl_video.srect.x = 0;
    sdl_video.srect.y = 0;
    if (sdl_video.srect.w > VIDEO_WIDTH)
    {
      sdl_video.srect.x = (sdl_video.srect.w - VIDEO_WIDTH) / 2;
      sdl_video.srect.w = VIDEO_WIDTH;
    }
    if (sdl_video.srect.h > VIDEO_HEIGHT)
    {
      sdl_video.srect.y = (sdl_video.srect.h - VIDEO_HEIGHT) / 2;
      sdl_video.srect.h = VIDEO_HEIGHT;
    }

    /* destination bitmap */
    sdl_video.drect.w = sdl_video.srect.w;
    sdl_video.drect.h = sdl_video.srect.h;
    sdl_video.drect.x = (VIDEO_WIDTH - sdl_video.drect.w) / 2;
    sdl_video.drect.y = (VIDEO_HEIGHT - sdl_video.drect.h) / 2;
    
    /* clear destination surface */
    SDL_FillRect(sdl_video.surf_screen, 0, 0);

    /*if (config.render && (interlaced || config.ntsc))  rect.h *= 2;
    if (config.ntsc) rect.w = (reg[12]&1) ? MD_NTSC_OUT_WIDTH(rect.w) : SMS_NTSC_OUT_WIDTH(rect.w);
    if (config.ntsc)
    {
      sms_ntsc = (sms_ntsc_t *)malloc(sizeof(sms_ntsc_t));
      md_ntsc = (md_ntsc_t *)malloc(sizeof(md_ntsc_t));

      switch (config.ntsc)
      {
        case 1:
          sms_ntsc_init(sms_ntsc, &sms_ntsc_composite);
          md_ntsc_init(md_ntsc, &md_ntsc_composite);
          break;
        case 2:
          sms_ntsc_init(sms_ntsc, &sms_ntsc_svideo);
          md_ntsc_init(md_ntsc, &md_ntsc_svideo);
          break;
        case 3:
          sms_ntsc_init(sms_ntsc, &sms_ntsc_rgb);
          md_ntsc_init(md_ntsc, &md_ntsc_rgb);
          break;
      }
    }
    else
    {
      if (sms_ntsc)
      {
        free(sms_ntsc);
        sms_ntsc = NULL;
      }

      if (md_ntsc)
      {
        free(md_ntsc);
        md_ntsc = NULL;
      }
    } */
  }

  SDL_BlitSurface(sdl_video.surf_bitmap, &sdl_video.srect, sdl_video.surf_screen, &sdl_video.drect);
  SDL_UpdateRect(sdl_video.surf_screen, 0, 0, 0, 0);

  ++sdl_video.frames_rendered;
}