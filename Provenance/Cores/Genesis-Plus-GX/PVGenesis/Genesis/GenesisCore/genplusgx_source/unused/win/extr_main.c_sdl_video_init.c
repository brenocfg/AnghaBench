#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ frames_rendered; int /*<<< orphan*/  surf_bitmap; int /*<<< orphan*/  surf_screen; } ;

/* Variables and functions */
 int /*<<< orphan*/  MessageBox (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_CreateRGBSurface (int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 scalar_t__ SDL_InitSubSystem (int /*<<< orphan*/ ) ; 
 int SDL_SWSURFACE ; 
 int /*<<< orphan*/  SDL_SetVideoMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SDL_ShowCursor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIDEO_HEIGHT ; 
 int /*<<< orphan*/  VIDEO_WIDTH ; 
 int fullscreen ; 
 TYPE_1__ sdl_video ; 

__attribute__((used)) static int sdl_video_init()
{
  if(SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
    MessageBox(NULL, "SDL Video initialization failed", "Error", 0);
    return 0;
  }
  sdl_video.surf_screen  = SDL_SetVideoMode(VIDEO_WIDTH, VIDEO_HEIGHT, 16, SDL_SWSURFACE | fullscreen);
  sdl_video.surf_bitmap = SDL_CreateRGBSurface(SDL_SWSURFACE, 720, 576, 16, 0, 0, 0, 0);
  sdl_video.frames_rendered = 0;
  SDL_ShowCursor(0);

  return 1;
}