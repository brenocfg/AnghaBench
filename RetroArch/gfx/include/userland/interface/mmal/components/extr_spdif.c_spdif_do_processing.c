#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_9__ ;
typedef  struct TYPE_35__   TYPE_8__ ;
typedef  struct TYPE_34__   TYPE_7__ ;
typedef  struct TYPE_33__   TYPE_6__ ;
typedef  struct TYPE_32__   TYPE_5__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;
typedef  struct TYPE_27__   TYPE_14__ ;
typedef  struct TYPE_26__   TYPE_10__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  ac3_spdif_header ;
struct TYPE_36__ {scalar_t__ status; } ;
struct TYPE_35__ {TYPE_6__** output; TYPE_6__** input; TYPE_3__* priv; } ;
struct TYPE_34__ {int /*<<< orphan*/  format; } ;
struct TYPE_33__ {TYPE_5__* priv; TYPE_14__* format; int /*<<< orphan*/  name; } ;
struct TYPE_32__ {scalar_t__ (* pf_set_format ) (TYPE_6__*) ;TYPE_4__* module; } ;
struct TYPE_31__ {int /*<<< orphan*/  queue; scalar_t__ needs_configuring; } ;
struct TYPE_30__ {TYPE_9__* module; } ;
struct TYPE_28__ {unsigned int sample_rate; } ;
struct TYPE_29__ {TYPE_1__ audio; } ;
struct TYPE_27__ {scalar_t__ encoding; TYPE_2__* es; } ;
struct TYPE_26__ {int length; int flags; unsigned int alloc_size; int* data; int offset; int /*<<< orphan*/  dts; scalar_t__ pts; scalar_t__ cmd; } ;
typedef  TYPE_6__ MMAL_PORT_T ;
typedef  TYPE_7__ MMAL_EVENT_FORMAT_CHANGED_T ;
typedef  TYPE_8__ MMAL_COMPONENT_T ;
typedef  TYPE_9__ MMAL_COMPONENT_MODULE_T ;
typedef  TYPE_10__ MMAL_BUFFER_HEADER_T ;
typedef  int MMAL_BOOL_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG (char*,int,...) ; 
 int /*<<< orphan*/  LOG_ERROR (char*,...) ; 
 int /*<<< orphan*/  LOG_INFO (char*,unsigned int,unsigned int) ; 
 int MMAL_BUFFER_HEADER_FLAG_CONFIG ; 
 scalar_t__ MMAL_EINVAL ; 
 scalar_t__ MMAL_ENCODING_EAC3 ; 
 int MMAL_MIN (unsigned int,unsigned int) ; 
 scalar_t__ MMAL_SUCCESS ; 
 unsigned int SPDIF_AC3_FRAME_SIZE ; 
 unsigned int SPDIF_EAC3_FRAME_SIZE ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  mmal_buffer_header_mem_lock (TYPE_10__*) ; 
 int /*<<< orphan*/  mmal_buffer_header_mem_unlock (TYPE_10__*) ; 
 scalar_t__ mmal_event_error_send (TYPE_8__*,scalar_t__) ; 
 TYPE_7__* mmal_event_format_changed_get (TYPE_10__*) ; 
 scalar_t__ mmal_format_full_copy (TYPE_14__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmal_port_buffer_header_callback (TYPE_6__*,TYPE_10__*) ; 
 TYPE_10__* mmal_queue_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmal_queue_put_back (int /*<<< orphan*/ ,TYPE_10__*) ; 
 int /*<<< orphan*/  spdif_send_event_format_changed (TYPE_8__*,TYPE_6__*,TYPE_14__*) ; 
 scalar_t__ stub1 (TYPE_6__*) ; 

__attribute__((used)) static MMAL_BOOL_T spdif_do_processing(MMAL_COMPONENT_T *component)
{
   static const uint8_t ac3_spdif_header[6] = {0x72,0xF8,0x1F,0x4E,0x1, 0};
   MMAL_COMPONENT_MODULE_T *module = component->priv->module;
   MMAL_PORT_T *port_in = component->input[0];
   MMAL_PORT_T *port_out = component->output[0];
   MMAL_BUFFER_HEADER_T *in, *out;
   unsigned int i, sample_rate, frame_size, spdif_frame_size;
   uint8_t *in_data;

   if (port_out->priv->module->needs_configuring)
      return 0;

   in = mmal_queue_get(port_in->priv->module->queue);
   if (!in)
      return 0;

   /* Handle event buffers */
   if (in->cmd)
   {
      MMAL_EVENT_FORMAT_CHANGED_T *event = mmal_event_format_changed_get(in);
      if (event)
      {
         module->status = mmal_format_full_copy(port_in->format, event->format);
         if (module->status == MMAL_SUCCESS)
            module->status = port_in->priv->pf_set_format(port_in);
         if (module->status != MMAL_SUCCESS)
         {
            LOG_ERROR("format not set on port %s %p (%i)", port_in->name, port_in, module->status);
            if (mmal_event_error_send(component, module->status) != MMAL_SUCCESS)
               LOG_ERROR("unable to send an error event buffer");
         }
      }
      else
      {
         LOG_ERROR("discarding event %i on port %s %p", (int)in->cmd, port_in->name, port_in);
      }

      in->length = 0;
      mmal_port_buffer_header_callback(port_in, in);
      return 1;
   }

   /* Don't do anything if we've already seen an error */
   if (module->status != MMAL_SUCCESS)
   {
      mmal_queue_put_back(port_in->priv->module->queue, in);
      return 0;
   }

   /* Discard empty buffers */
   if (!in->length && !in->flags)
   {
      mmal_port_buffer_header_callback(port_in, in);
      return 1;
   }
   /* Discard codec config data as it's not needed */
   if (in->flags & MMAL_BUFFER_HEADER_FLAG_CONFIG)
   {
      LOG_DEBUG("config buffer %ibytes", in->length);
      in->length = 0;
      mmal_port_buffer_header_callback(port_in, in);
      return 1;
   }

   out = mmal_queue_get(port_out->priv->module->queue);
   if (!out)
   {
      mmal_queue_put_back(port_in->priv->module->queue, in);
      return 0;
   }

   spdif_frame_size = SPDIF_AC3_FRAME_SIZE;
   if (port_out->format->encoding == MMAL_ENCODING_EAC3)
      spdif_frame_size = SPDIF_EAC3_FRAME_SIZE;

   /* Sanity check the output buffer is big enough */
   if (out->alloc_size < spdif_frame_size)
   {
      module->status = MMAL_EINVAL;
      if (mmal_event_error_send(component, module->status) != MMAL_SUCCESS)
         LOG_ERROR("unable to send an error event buffer");
      mmal_queue_put_back(port_in->priv->module->queue, in);
      mmal_queue_put_back(port_out->priv->module->queue, out);
      return 0;
   }

   /* Special case for empty buffers carrying a flag */
   if (!in->length && in->flags)
   {
      out->length = 0;
      goto end;
   }

   LOG_DEBUG("frame: %lld, size %i", in->pts, in->length);
   mmal_buffer_header_mem_lock(out);
   mmal_buffer_header_mem_lock(in);
   in_data = in->data + in->offset;

   /* Sanity check we're dealing with an AC3 frame */
   if (in->length < 5)
   {
      LOG_ERROR("invalid data size (%i bytes)", in->length);
      goto discard;
   }

   if (!(in_data[0] == 0x0B || in_data[1] == 0x77) &&
       !(in_data[0] == 0x77 || in_data[1] == 0x0B))
   {
      LOG_ERROR("invalid data (%i bytes): %2.2x,%2.2x,%2.2x,%2.2x",
         in->length, in_data[0], in_data[1], in_data[2], in_data[3]);
      goto discard;
   }

   /* We need to make sure we use the right sample rate
    * to be able to play this at the right rate */
   if ((in_data[4] & 0xC0) == 0x40) sample_rate = 44100;
   else if ((in_data[4] & 0xC0) == 0x80) sample_rate = 32000;
   else sample_rate = 48000;

   /* If the sample rate changes, stop everything we're doing
    * and signal the format change. */
   if (sample_rate != port_out->format->es->audio.sample_rate)
   {
      LOG_INFO("format change: %i->%i",
         port_out->format->es->audio.sample_rate, sample_rate);
      port_in->format->es->audio.sample_rate = sample_rate;
      spdif_send_event_format_changed(component, port_out, port_in->format);
      mmal_buffer_header_mem_unlock(in);
      mmal_buffer_header_mem_unlock(out);
      mmal_queue_put_back(port_in->priv->module->queue, in);
      mmal_queue_put_back(port_out->priv->module->queue, out);
      return 0;
   }

   /* Build our S/PDIF frame. We assume that we need to send
    * little endian S/PDIF data. */
   if (in->length > spdif_frame_size - 8)
      LOG_ERROR("frame too big, truncating (%i/%i bytes)",
         in->length, spdif_frame_size - 8);
   frame_size = MMAL_MIN(in->length, spdif_frame_size - 8) / 2;
   memcpy(out->data, ac3_spdif_header, sizeof(ac3_spdif_header));
   out->data[5] = in_data[5] & 0x7; /* bsmod */
   out->data[6] = frame_size & 0xFF;
   out->data[7] = frame_size >> 8;

   /* Copy the AC3 data, reverting the endianness if required */
   if (in_data[0] == 0x0B)
   {
      for (i = 0; i < frame_size; i++)
      {
         out->data[8+i*2] = in_data[in->offset+i*2+1];
         out->data[8+i*2+1] = in_data[in->offset+i*2];
      }
   }
   else
      memcpy(out->data + 8, in_data, in->length);

   /* The S/PDIF frame needs to be padded */
   memset(out->data + 8 + frame_size * 2, 0,
      spdif_frame_size - frame_size * 2 - 8);
   mmal_buffer_header_mem_unlock(in);
   mmal_buffer_header_mem_unlock(out);
   out->length     = spdif_frame_size;
 end:
   out->offset     = 0;
   out->flags      = in->flags;
   out->pts        = in->pts;
   out->dts        = in->dts;

   /* Send buffers back */
   in->length = 0;
   mmal_port_buffer_header_callback(port_in, in);
   mmal_port_buffer_header_callback(port_out, out);
   return 1;

 discard:
   mmal_buffer_header_mem_unlock(in);
   mmal_buffer_header_mem_unlock(out);
   in->length = 0;
   mmal_queue_put_back(port_out->priv->module->queue, out);
   mmal_port_buffer_header_callback(port_in, in);
   return 1;
}