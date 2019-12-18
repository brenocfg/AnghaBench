#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  scaler; scalar_t__ frame; } ;
struct TYPE_7__ {TYPE_1__ menu; int /*<<< orphan*/  scaler; scalar_t__ font; TYPE_2__* font_driver; } ;
typedef  TYPE_3__ sdl_video_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* free ) (scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_FreeSurface (scalar_t__) ; 
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 int /*<<< orphan*/  SDL_QuitSubSystem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  scaler_ctx_gen_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

__attribute__((used)) static void sdl_gfx_free(void *data)
{
   sdl_video_t *vid = (sdl_video_t*)data;
   if (!vid)
      return;

   if (vid->menu.frame)
      SDL_FreeSurface(vid->menu.frame);

   SDL_QuitSubSystem(SDL_INIT_VIDEO);

   if (vid->font)
      vid->font_driver->free(vid->font);

   scaler_ctx_gen_reset(&vid->scaler);
   scaler_ctx_gen_reset(&vid->menu.scaler);

   free(vid);
}