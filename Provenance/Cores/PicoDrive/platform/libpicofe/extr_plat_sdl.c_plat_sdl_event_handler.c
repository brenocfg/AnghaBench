#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct TYPE_12__ {int /*<<< orphan*/  vout_fullscreen; int /*<<< orphan*/  vout_method; } ;
struct TYPE_9__ {int gain; } ;
struct TYPE_8__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct TYPE_11__ {int type; TYPE_2__ active; TYPE_1__ resize; } ;
struct TYPE_10__ {int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ SDL_Rect ;
typedef  TYPE_4__ SDL_Event ;

/* Variables and functions */
 int GL_QUIRK_ACTIVATE_RECREATE ; 
#define  SDL_ACTIVEEVENT 130 
 int /*<<< orphan*/  SDL_DisplayYUVOverlay (int /*<<< orphan*/ *,TYPE_3__*) ; 
#define  SDL_QUIT 129 
#define  SDL_VIDEORESIZE 128 
 int /*<<< orphan*/  display ; 
 int /*<<< orphan*/  gl_finish () ; 
 int /*<<< orphan*/  gl_flip (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int gl_quirks ; 
 int /*<<< orphan*/  old_fullscreen ; 
 int /*<<< orphan*/  plat_sdl_change_video_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int plat_sdl_gl_active ; 
 int /*<<< orphan*/ * plat_sdl_overlay ; 
 int /*<<< orphan*/  plat_sdl_quit_cb () ; 
 TYPE_6__* plat_sdl_screen ; 
 TYPE_5__ plat_target ; 
 int /*<<< orphan*/  window ; 
 int /*<<< orphan*/  window_h ; 
 int /*<<< orphan*/  window_w ; 

void plat_sdl_event_handler(void *event_)
{
  static int was_active;
  SDL_Event *event = event_;

  switch (event->type) {
  case SDL_VIDEORESIZE:
    //printf("resize %dx%d\n", event->resize.w, event->resize.h);
    if (plat_target.vout_method != 0
        && !plat_target.vout_fullscreen && !old_fullscreen)
    {
      window_w = event->resize.w;
      window_h = event->resize.h;
      plat_sdl_change_video_mode(0, 0, 1);
    }
    break;
  case SDL_ACTIVEEVENT:
    if (event->active.gain && !was_active) {
      if (plat_sdl_overlay != NULL) {
        SDL_Rect dstrect = { 0, 0, plat_sdl_screen->w, plat_sdl_screen->h };
        SDL_DisplayYUVOverlay(plat_sdl_overlay, &dstrect);
      }
      else if (plat_sdl_gl_active) {
        if (gl_quirks & GL_QUIRK_ACTIVATE_RECREATE) {
          gl_finish();
          plat_sdl_gl_active = (gl_init(display, window, &gl_quirks) == 0);
        }
        gl_flip(NULL, 0, 0);
      }
      // else SDL takes care of it
    }
    was_active = event->active.gain;
    break;
  case SDL_QUIT:
    if (plat_sdl_quit_cb != NULL)
      plat_sdl_quit_cb();
    break;
  }
}