#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int width; int height; scalar_t__ sdl_overlay; int /*<<< orphan*/  sdl_surface; } ;
struct TYPE_15__ {TYPE_1__* priv; } ;
struct TYPE_14__ {int buffer_size_min; TYPE_4__* format; TYPE_6__* component; } ;
struct TYPE_13__ {scalar_t__ encoding; TYPE_3__* es; } ;
struct TYPE_11__ {int width; int height; } ;
struct TYPE_12__ {TYPE_2__ video; } ;
struct TYPE_10__ {TYPE_7__* module; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_5__ MMAL_PORT_T ;
typedef  TYPE_6__ MMAL_COMPONENT_T ;
typedef  TYPE_7__ MMAL_COMPONENT_MODULE_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*) ; 
 scalar_t__ MMAL_ENCODING_I420 ; 
 int /*<<< orphan*/  MMAL_ENOSPC ; 
 int /*<<< orphan*/  MMAL_ENOSYS ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 scalar_t__ SDL_CreateYUVOverlay (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_FreeYUVOverlay (scalar_t__) ; 
 int /*<<< orphan*/  SDL_YV12_OVERLAY ; 
 int /*<<< orphan*/  mmal_sdl_create_surface (TYPE_7__*) ; 

__attribute__((used)) static MMAL_STATUS_T sdl_port_set_format(MMAL_PORT_T *port)
{
   MMAL_COMPONENT_T *component = port->component;
   MMAL_COMPONENT_MODULE_T *module = component->priv->module;
   MMAL_STATUS_T status;

   if ((status=mmal_sdl_create_surface(module)) != MMAL_SUCCESS)
      return status;

   /* We only support I420 */
   if (port->format->encoding != MMAL_ENCODING_I420)
      return MMAL_ENOSYS;

   /* Check if we need to re-create an overlay */
   if (module->sdl_overlay &&
       module->width == port->format->es->video.width &&
       module->height == port->format->es->video.height)
      return MMAL_SUCCESS; /* Nothing to do */

   if (module->sdl_overlay)
      SDL_FreeYUVOverlay(module->sdl_overlay);

   /* Create overlay */
   module->sdl_overlay =
      SDL_CreateYUVOverlay(port->format->es->video.width,
                           port->format->es->video.height,
                           SDL_YV12_OVERLAY, module->sdl_surface);
   if (!module->sdl_overlay)
   {
      LOG_ERROR("cannot create SDL overlay");
      return MMAL_ENOSPC;
   }
   module->width = port->format->es->video.width;
   module->height = port->format->es->video.height;

   port->buffer_size_min = module->width * module->height * 3 / 2;
   return MMAL_SUCCESS;
}