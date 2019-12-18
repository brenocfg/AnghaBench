#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  quit; } ;
struct TYPE_9__ {TYPE_1__* priv; } ;
struct TYPE_8__ {int type; } ;
struct TYPE_7__ {TYPE_4__* module; } ;
typedef  TYPE_2__ SDL_Event ;
typedef  TYPE_3__ MMAL_COMPONENT_T ;
typedef  TYPE_4__ MMAL_COMPONENT_MODULE_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_SUCCESS ; 
#define  SDL_QUIT 128 
 scalar_t__ SDL_WaitEvent (TYPE_2__*) ; 
 int /*<<< orphan*/  mmal_event_error_send (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sdl_event_thread(void *arg)
{
   MMAL_COMPONENT_T *component = (MMAL_COMPONENT_T *)arg;
   MMAL_COMPONENT_MODULE_T *module = component->priv->module;
   SDL_Event event;

   while (SDL_WaitEvent(&event))
   {
      switch (event.type)
      {
      case SDL_QUIT:
         if (!module->quit)
            mmal_event_error_send(component, MMAL_SUCCESS);
         return 0;
      default:
         break;
      }
   }

   return 0;
}