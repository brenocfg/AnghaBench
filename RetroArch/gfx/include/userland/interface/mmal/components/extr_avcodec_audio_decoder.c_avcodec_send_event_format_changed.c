#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_11__ ;

/* Type definitions */
struct TYPE_23__ {scalar_t__ status; int output_needs_configuring; TYPE_4__* codec_context; } ;
struct TYPE_22__ {TYPE_1__* priv; } ;
struct TYPE_21__ {int /*<<< orphan*/  buffer_num_recommended; int /*<<< orphan*/  buffer_size_min; int /*<<< orphan*/  buffer_size_recommended; int /*<<< orphan*/  buffer_num_min; TYPE_11__* format; } ;
struct TYPE_20__ {int /*<<< orphan*/  buffer_num_recommended; int /*<<< orphan*/  buffer_size_min; int /*<<< orphan*/  buffer_num_min; int /*<<< orphan*/  format; } ;
struct TYPE_19__ {int /*<<< orphan*/  sample_fmt; int /*<<< orphan*/  channels; int /*<<< orphan*/  sample_rate; } ;
struct TYPE_17__ {int /*<<< orphan*/  bits_per_sample; int /*<<< orphan*/  channels; int /*<<< orphan*/  sample_rate; } ;
struct TYPE_18__ {TYPE_2__ audio; } ;
struct TYPE_16__ {TYPE_8__* module; } ;
struct TYPE_15__ {TYPE_3__* es; int /*<<< orphan*/  encoding; } ;
typedef  TYPE_5__ MMAL_PORT_T ;
typedef  TYPE_6__ MMAL_EVENT_FORMAT_CHANGED_T ;
typedef  TYPE_7__ MMAL_COMPONENT_T ;
typedef  TYPE_8__ MMAL_COMPONENT_MODULE_T ;
typedef  int /*<<< orphan*/  MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*) ; 
 int /*<<< orphan*/  MMAL_EVENT_FORMAT_CHANGED ; 
 scalar_t__ MMAL_SUCCESS ; 
 TYPE_6__* mmal_event_format_changed_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmal_format_copy (TYPE_11__*,int /*<<< orphan*/ ) ; 
 scalar_t__ mmal_port_event_get (TYPE_5__*,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmal_port_event_send (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  samplefmt_to_encoding (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  samplefmt_to_sample_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void avcodec_send_event_format_changed(MMAL_COMPONENT_T *component, MMAL_PORT_T *port)
{
   MMAL_COMPONENT_MODULE_T *module = component->priv->module;
   MMAL_BUFFER_HEADER_T *buffer = NULL;
   MMAL_EVENT_FORMAT_CHANGED_T *event;

   /* Get an event buffer */
   module->status = mmal_port_event_get(port, &buffer, MMAL_EVENT_FORMAT_CHANGED);
   if (module->status != MMAL_SUCCESS)
   {
      LOG_ERROR("unable to get an event buffer");
      return;
   }
   event = mmal_event_format_changed_get(buffer);

   /* Fill in the new format */
   mmal_format_copy(event->format, port->format);
   event->format->es->audio.sample_rate = module->codec_context->sample_rate;
   event->format->es->audio.channels = module->codec_context->channels;
   event->format->encoding = samplefmt_to_encoding(module->codec_context->sample_fmt);
   event->format->es->audio.bits_per_sample = samplefmt_to_sample_size(module->codec_context->sample_fmt);

   /* Pass on the buffer requirements */
   event->buffer_num_min = port->buffer_num_min;
   event->buffer_size_min = port->buffer_size_min;
   event->buffer_size_recommended = event->buffer_size_min;
   event->buffer_num_recommended = port->buffer_num_recommended;

   module->output_needs_configuring = 1;
   mmal_port_event_send(port, buffer);
}