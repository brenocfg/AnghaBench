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
typedef  int /*<<< orphan*/  video_frame_info_t ;
typedef  void gfx_ctx_sdl_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_LOG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RARCH_WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_GetError () ; 
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 scalar_t__ SDL_Init (int /*<<< orphan*/ ) ; 
 scalar_t__ SDL_InitSubSystem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_MAJOR_VERSION ; 
 int /*<<< orphan*/  SDL_MINOR_VERSION ; 
 int /*<<< orphan*/  SDL_PATCHLEVEL ; 
 scalar_t__ SDL_WasInit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XInitThreads () ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  sdl_ctx_destroy_resources (void*) ; 

__attribute__((used)) static void *sdl_ctx_init(video_frame_info_t *video_info, void *video_driver)
{
   gfx_ctx_sdl_data_t *sdl = (gfx_ctx_sdl_data_t*)
      calloc(1, sizeof(gfx_ctx_sdl_data_t));

   if (!sdl)
      return NULL;

#ifdef HAVE_X11
   XInitThreads();
#endif

   if (SDL_WasInit(0) == 0)
   {
      if (SDL_Init(SDL_INIT_VIDEO) < 0)
         goto error;
   }
   else if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
      goto error;

   RARCH_LOG("[SDL_GL] SDL %i.%i.%i gfx context driver initialized.\n",
           SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_PATCHLEVEL);

   return sdl;

error:
   RARCH_WARN("[SDL_GL]: Failed to initialize SDL gfx context driver: %s\n",
              SDL_GetError());

   sdl_ctx_destroy_resources(sdl);

   if (sdl)
      free(sdl);

   return NULL;
}