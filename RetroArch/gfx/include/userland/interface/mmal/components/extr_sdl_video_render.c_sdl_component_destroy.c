#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ queue; scalar_t__ sdl_surface; scalar_t__ sdl_overlay; scalar_t__ thread; int /*<<< orphan*/  quit; } ;
struct TYPE_10__ {int /*<<< orphan*/  input; scalar_t__ input_num; TYPE_1__* priv; } ;
struct TYPE_9__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_8__ {TYPE_4__* module; } ;
typedef  TYPE_2__ SDL_Event ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_3__ MMAL_COMPONENT_T ;
typedef  TYPE_4__ MMAL_COMPONENT_MODULE_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 int /*<<< orphan*/  MMAL_TRUE ; 
 int /*<<< orphan*/  SDL_FreeSurface (scalar_t__) ; 
 int /*<<< orphan*/  SDL_FreeYUVOverlay (scalar_t__) ; 
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 int /*<<< orphan*/  SDL_PushEvent (TYPE_2__*) ; 
 int /*<<< orphan*/  SDL_QUIT ; 
 int /*<<< orphan*/  SDL_QuitSubSystem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_WaitThread (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmal_ports_free (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmal_queue_destroy (scalar_t__) ; 
 int /*<<< orphan*/  vcos_free (TYPE_4__*) ; 

__attribute__((used)) static MMAL_STATUS_T sdl_component_destroy(MMAL_COMPONENT_T *component)
{
   MMAL_COMPONENT_MODULE_T *module = component->priv->module;
   SDL_Event event = {SDL_QUIT};

   module->quit = MMAL_TRUE;
   SDL_PushEvent(&event);
   if(module->thread)
      SDL_WaitThread(module->thread, NULL);
   if(module->sdl_overlay)
      SDL_FreeYUVOverlay(module->sdl_overlay);
   if(module->sdl_surface)
      SDL_FreeSurface(module->sdl_surface);
   SDL_QuitSubSystem(SDL_INIT_VIDEO);

   if(component->input_num) mmal_ports_free(component->input, 1);
   if(module->queue) mmal_queue_destroy(module->queue);
   vcos_free(module);
   return MMAL_SUCCESS;
}