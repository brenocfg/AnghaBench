#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {int width; int height; } ;
struct TYPE_5__ {int /*<<< orphan*/  sdl_surface; TYPE_1__ display_region; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_2__ MMAL_COMPONENT_MODULE_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*) ; 
 int /*<<< orphan*/  MMAL_ENOMEM ; 
 int /*<<< orphan*/  MMAL_ENOSYS ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 int SDL_ANYFORMAT ; 
 int SDL_DOUBLEBUF ; 
 int SDL_HWPALETTE ; 
 int SDL_HWSURFACE ; 
 int SDL_RESIZABLE ; 
 int /*<<< orphan*/  SDL_SetVideoMode (int,int,int,int) ; 
 int SDL_VideoModeOK (int,int,int,int) ; 

__attribute__((used)) static MMAL_STATUS_T mmal_sdl_create_surface(MMAL_COMPONENT_MODULE_T *module)
{
   uint32_t flags;
   int bpp;
   int w = module->display_region.width;
   int h = module->display_region.height;

   flags = SDL_ANYFORMAT | SDL_HWPALETTE | SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE;
   bpp = SDL_VideoModeOK(w, h, 16, flags);
   if(!bpp)
   {
      LOG_ERROR("no SDL video mode available");
      return MMAL_ENOSYS;
   }
   module->sdl_surface = SDL_SetVideoMode(w, h, bpp, flags);
   if(!module->sdl_surface)
   {
      LOG_ERROR("cannot create SDL surface");
      return MMAL_ENOMEM;
   }
   return MMAL_SUCCESS;
}