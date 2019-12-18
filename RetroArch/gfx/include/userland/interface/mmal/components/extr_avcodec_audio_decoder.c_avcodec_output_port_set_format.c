#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ bits_per_sample; scalar_t__ output_needs_configuring; scalar_t__ channels; scalar_t__ sample_rate; TYPE_1__* codec_context; int /*<<< orphan*/  sample_fmt; } ;
struct TYPE_17__ {TYPE_5__* priv; } ;
struct TYPE_16__ {TYPE_7__* component; TYPE_4__* format; } ;
struct TYPE_15__ {TYPE_8__* module; } ;
struct TYPE_14__ {scalar_t__ encoding; TYPE_3__* es; } ;
struct TYPE_12__ {scalar_t__ bits_per_sample; scalar_t__ channels; scalar_t__ sample_rate; } ;
struct TYPE_13__ {TYPE_2__ audio; } ;
struct TYPE_11__ {int /*<<< orphan*/  sample_fmt; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_6__ MMAL_PORT_T ;
typedef  TYPE_7__ MMAL_COMPONENT_T ;
typedef  TYPE_8__ MMAL_COMPONENT_MODULE_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_EINVAL ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 int /*<<< orphan*/  mmal_component_action_trigger (TYPE_7__*) ; 
 scalar_t__ samplefmt_to_encoding (int /*<<< orphan*/ ) ; 
 scalar_t__ samplefmt_to_sample_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static MMAL_STATUS_T avcodec_output_port_set_format(MMAL_PORT_T *port)
{
   MMAL_COMPONENT_T *component = port->component;
   MMAL_COMPONENT_MODULE_T *module = component->priv->module;

   /* Format can only be set to what is output by the codec */
   if (samplefmt_to_encoding(module->codec_context->sample_fmt) != port->format->encoding ||
       samplefmt_to_sample_size(module->codec_context->sample_fmt) != port->format->es->audio.bits_per_sample)
      return MMAL_EINVAL;

   if (!port->format->es->audio.sample_rate || !port->format->es->audio.channels)
      return MMAL_EINVAL;

   module->sample_fmt = module->codec_context->sample_fmt;
   module->sample_rate = port->format->es->audio.sample_rate;
   module->channels = port->format->es->audio.channels;
   module->bits_per_sample = port->format->es->audio.bits_per_sample;

   port->component->priv->module->output_needs_configuring = 0;
   mmal_component_action_trigger(port->component);

   return MMAL_SUCCESS;
}