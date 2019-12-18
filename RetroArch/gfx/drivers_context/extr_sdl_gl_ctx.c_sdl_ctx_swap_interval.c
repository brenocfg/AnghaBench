#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  SDL_GL_SWAP_CONTROL ; 
 int /*<<< orphan*/  SDL_GL_SetAttribute (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SDL_GL_SetSwapInterval (int) ; 

__attribute__((used)) static void sdl_ctx_swap_interval(void *data, int interval)
{
   (void)data;
#ifdef HAVE_SDL2
   SDL_GL_SetSwapInterval(interval);
#else
   SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, interval);
#endif
}