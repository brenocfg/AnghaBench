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
struct TYPE_2__ {int /*<<< orphan*/  window; } ;
typedef  TYPE_1__ sdl2_video_t ;

/* Variables and functions */
 unsigned int SDL_GetWindowFlags (int /*<<< orphan*/ ) ; 
 unsigned int SDL_WINDOW_INPUT_FOCUS ; 
 unsigned int SDL_WINDOW_MOUSE_FOCUS ; 

__attribute__((used)) static bool sdl2_gfx_focus(void *data)
{
   sdl2_video_t *vid = (sdl2_video_t*)data;
   unsigned flags = (SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS);
   return (SDL_GetWindowFlags(vid->window) & flags) == flags;
}