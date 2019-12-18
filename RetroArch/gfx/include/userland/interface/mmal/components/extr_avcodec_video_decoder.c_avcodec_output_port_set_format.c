#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/ * data; } ;
struct TYPE_20__ {scalar_t__ frame_size; int planes; scalar_t__ output_needs_configuring; TYPE_10__ layout; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  pix_fmt; TYPE_1__* codec_context; } ;
struct TYPE_19__ {TYPE_5__* priv; } ;
struct TYPE_18__ {scalar_t__ buffer_size_min; TYPE_7__* component; TYPE_4__* format; } ;
struct TYPE_17__ {TYPE_8__* module; } ;
struct TYPE_16__ {scalar_t__ encoding; TYPE_3__* es; } ;
struct TYPE_14__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_15__ {TYPE_2__ video; } ;
struct TYPE_13__ {int /*<<< orphan*/  pix_fmt; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_6__ MMAL_PORT_T ;
typedef  TYPE_7__ MMAL_COMPONENT_T ;
typedef  TYPE_8__ MMAL_COMPONENT_MODULE_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_EINVAL ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 scalar_t__ avpicture_fill (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmal_component_action_trigger (TYPE_7__*) ; 
 scalar_t__ pixfmt_to_encoding (int /*<<< orphan*/ ) ; 

__attribute__((used)) static MMAL_STATUS_T avcodec_output_port_set_format(MMAL_PORT_T *port)
{
   MMAL_COMPONENT_T *component = port->component;
   MMAL_COMPONENT_MODULE_T *module = component->priv->module;

   /* Format can only be set to what is output by the codec */
   if (pixfmt_to_encoding(module->codec_context->pix_fmt) != port->format->encoding)
      return MMAL_EINVAL;

   module->pix_fmt = module->codec_context->pix_fmt;
   module->width = port->format->es->video.width;
   module->height = port->format->es->video.height;

   module->frame_size =
      avpicture_fill(&module->layout, 0, module->pix_fmt, module->width, module->height);
   if (module->frame_size < 0)
      return MMAL_EINVAL;

   /* Calculate the number of planes for this format */
   for (module->planes = 0; module->planes < 4; )
      if (!module->layout.data[module->planes++])
         break;

   port->buffer_size_min = module->frame_size;
   port->component->priv->module->output_needs_configuring = 0;
   mmal_component_action_trigger(port->component);

   return MMAL_SUCCESS;
}