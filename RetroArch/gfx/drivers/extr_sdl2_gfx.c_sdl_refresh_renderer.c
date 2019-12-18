#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ height; scalar_t__ width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_7__ {TYPE_1__ vp; int /*<<< orphan*/  renderer; } ;
typedef  TYPE_2__ sdl2_video_t ;
struct TYPE_8__ {int w; int h; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_3__ SDL_Rect ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_RenderClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_RenderSetLogicalSize (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SDL_RenderSetViewport (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static void sdl_refresh_renderer(sdl2_video_t *vid)
{
   SDL_Rect r;

   SDL_RenderClear(vid->renderer);

   r.x      = vid->vp.x;
   r.y      = vid->vp.y;
   r.w      = (int)vid->vp.width;
   r.h      = (int)vid->vp.height;

   SDL_RenderSetViewport(vid->renderer, &r);

   /* breaks int scaling */
#if 0
   SDL_RenderSetLogicalSize(vid->renderer, vid->vp.width, vid->vp.height);
#endif
}