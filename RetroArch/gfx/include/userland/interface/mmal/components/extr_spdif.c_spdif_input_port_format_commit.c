#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ encoding; TYPE_2__* es; int /*<<< orphan*/  bitrate; } ;
struct TYPE_16__ {TYPE_3__** output; } ;
struct TYPE_15__ {TYPE_7__* format; int /*<<< orphan*/  is_enabled; TYPE_4__* component; } ;
struct TYPE_13__ {scalar_t__ sample_rate; int /*<<< orphan*/  channels; } ;
struct TYPE_14__ {TYPE_1__ audio; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_3__ MMAL_PORT_T ;
typedef  TYPE_4__ MMAL_COMPONENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_INFO (char*,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MMAL_ENCODING_AC3 ; 
 scalar_t__ MMAL_ENCODING_EAC3 ; 
 scalar_t__ MMAL_ENCODING_PCM_SIGNED ; 
 int /*<<< orphan*/  MMAL_ENXIO ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 int /*<<< orphan*/  mmal_format_compare (TYPE_7__*,TYPE_7__*) ; 
 int /*<<< orphan*/  mmal_format_copy (TYPE_7__*,TYPE_7__*) ; 
 int /*<<< orphan*/  spdif_send_event_format_changed (TYPE_4__*,TYPE_3__*,TYPE_7__*) ; 

__attribute__((used)) static MMAL_STATUS_T spdif_input_port_format_commit(MMAL_PORT_T *in)
{
   MMAL_COMPONENT_T *component = in->component;
   MMAL_PORT_T *out = component->output[0];

   /* Sanity check we cope with this format */
   if (in->format->encoding != MMAL_ENCODING_AC3 &&
       in->format->encoding != MMAL_ENCODING_EAC3)
      return MMAL_ENXIO;

   LOG_INFO("%4.4s, %iHz, %ichan, %ibps", (char *)&in->format->encoding,
      in->format->es->audio.sample_rate, in->format->es->audio.channels,
      in->format->bitrate);

   /* TODO: should we check the bitrate to see if that fits in an S/PDIF
    * frame? */

   /* Check if there's anything to propagate to the output port */
   if (!mmal_format_compare(in->format, out->format))
      return MMAL_SUCCESS;
   if (out->format->encoding == MMAL_ENCODING_PCM_SIGNED &&
       in->format->es->audio.sample_rate ==
          out->format->es->audio.sample_rate)
      return MMAL_SUCCESS;

   /* If the output port is not enabled we just need to update its format.
    * Otherwise we'll have to trigger a format changed event for it. */
   if (!out->is_enabled)
   {
      if (out->format->encoding != MMAL_ENCODING_PCM_SIGNED)
         mmal_format_copy(out->format, in->format);
      out->format->es->audio.sample_rate = in->format->es->audio.sample_rate;
      return MMAL_SUCCESS;
   }

   /* Send an event on the output port */
   return spdif_send_event_format_changed(component, out, in->format);
}