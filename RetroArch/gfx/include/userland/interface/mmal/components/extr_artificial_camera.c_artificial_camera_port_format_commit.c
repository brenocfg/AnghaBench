#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int planes; unsigned int* pitch; unsigned int* offset; } ;
struct TYPE_15__ {unsigned int frame_size; TYPE_5__ frame; } ;
struct TYPE_14__ {unsigned int buffer_size_min; unsigned int buffer_size_recommended; TYPE_4__* format; TYPE_1__* priv; } ;
struct TYPE_12__ {int encoding; TYPE_3__* es; } ;
struct TYPE_10__ {unsigned int width; unsigned int height; } ;
struct TYPE_11__ {TYPE_2__ video; } ;
struct TYPE_9__ {TYPE_7__* module; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_6__ MMAL_PORT_T ;
typedef  TYPE_7__ MMAL_PORT_MODULE_T ;

/* Variables and functions */
#define  MMAL_ENCODING_I420 130 
#define  MMAL_ENCODING_I422 129 
#define  MMAL_ENCODING_NV21 128 
 int /*<<< orphan*/  MMAL_ENOSYS ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 

__attribute__((used)) static MMAL_STATUS_T artificial_camera_port_format_commit(MMAL_PORT_T *port)
{
   MMAL_PORT_MODULE_T *port_module = port->priv->module;
   unsigned int width = port->format->es->video.width;
   unsigned int height = port->format->es->video.height;
   width = (width + 31) & ~31;
   height = (height + 15) & ~15;

   /* We only support a few formats */
   switch(port->format->encoding)
   {
   case MMAL_ENCODING_I420:
      port_module->frame_size = width * height * 3 / 2;
      port_module->frame.planes = 3;
      port_module->frame.pitch[0] = width;
      port_module->frame.offset[1] = port_module->frame.pitch[0] * height;
      port_module->frame.pitch[1] = width / 2;
      port_module->frame.offset[2] = port_module->frame.offset[1] + port_module->frame.pitch[1] * height / 2;
      port_module->frame.pitch[2] = width / 2;
      break;
   case MMAL_ENCODING_NV21:
      port_module->frame_size = width * height * 3 / 2;
      port_module->frame.planes = 2;
      port_module->frame.pitch[0] = width;
      port_module->frame.offset[1] = port_module->frame.pitch[0] * height;
      port_module->frame.pitch[1] = width;
      break;
   case MMAL_ENCODING_I422:
      port_module->frame_size = width * height * 2;
      port_module->frame.planes = 3;
      port_module->frame.pitch[0] = width;
      port_module->frame.offset[1] = port_module->frame.pitch[0] * height;
      port_module->frame.pitch[1] = width / 2;
      port_module->frame.offset[2] = port_module->frame.offset[1] + port_module->frame.pitch[1] * height;
      port_module->frame.pitch[2] = width / 2;
      break;
   default:
      return MMAL_ENOSYS;
   }

   port->buffer_size_min = port->buffer_size_recommended = port_module->frame_size;
   return MMAL_SUCCESS;
}