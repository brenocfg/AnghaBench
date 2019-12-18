#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_13__ ;
typedef  struct TYPE_16__   TYPE_12__ ;

/* Type definitions */
struct TYPE_22__ {int size; scalar_t__ data; } ;
struct TYPE_21__ {int length; int flags; scalar_t__ alloc_size; scalar_t__ dts; scalar_t__ offset; scalar_t__ data; int /*<<< orphan*/  pts; } ;
struct TYPE_20__ {scalar_t__ pts; int /*<<< orphan*/  queue_in; scalar_t__ picture_available; TYPE_13__* picture; TYPE_12__* codec_context; scalar_t__ output_needs_configuring; } ;
struct TYPE_19__ {int /*<<< orphan*/ ** output; int /*<<< orphan*/ ** input; TYPE_1__* priv; } ;
struct TYPE_18__ {TYPE_3__* module; } ;
struct TYPE_17__ {scalar_t__ reordered_opaque; } ;
struct TYPE_16__ {int /*<<< orphan*/  reordered_opaque; } ;
typedef  int /*<<< orphan*/  MMAL_PORT_T ;
typedef  TYPE_2__ MMAL_COMPONENT_T ;
typedef  TYPE_3__ MMAL_COMPONENT_MODULE_T ;
typedef  TYPE_4__ MMAL_BUFFER_HEADER_T ;
typedef  int MMAL_BOOL_T ;
typedef  TYPE_5__ AVPacket ;

/* Variables and functions */
 scalar_t__ FF_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  LOG_ERROR (char*,int) ; 
 int /*<<< orphan*/  LOG_WARN (char*) ; 
 int MMAL_BUFFER_HEADER_FLAG_EOS ; 
 scalar_t__ MMAL_SUCCESS ; 
 scalar_t__ MMAL_TIME_UNKNOWN ; 
 int /*<<< orphan*/  av_init_packet (TYPE_5__*) ; 
 int avcodec_decode_video2 (TYPE_12__*,TYPE_13__*,scalar_t__*,TYPE_5__*) ; 
 scalar_t__ avcodec_send_eos (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ avcodec_send_picture (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mmal_port_buffer_header_callback (int /*<<< orphan*/ *,TYPE_4__*) ; 
 TYPE_4__* mmal_queue_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmal_queue_put_back (int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static MMAL_BOOL_T avcodec_do_processing(MMAL_COMPONENT_T *component)
{
   MMAL_COMPONENT_MODULE_T *module = component->priv->module;
   MMAL_PORT_T *port_in = component->input[0];
   MMAL_PORT_T *port_out = component->output[0];
   MMAL_BUFFER_HEADER_T *in;
   AVPacket avpkt;
   int used = 0;

   if (module->output_needs_configuring)
      return 0;

   if (module->picture_available &&
       avcodec_send_picture(component, port_out) != MMAL_SUCCESS)
      return 0;

   module->picture_available = 0;

   /* Get input buffer to decode */
   in = mmal_queue_get(module->queue_in);
   if (!in)
      return 0;

   /* Discard empty buffers. EOS buffers are not discarded since they will be used
    * to flush the codec. */
   if (!in->length && !(in->flags & MMAL_BUFFER_HEADER_FLAG_EOS))
      goto end;

   /* Avcodec expects padded input data */
   if (in->length && !in->offset)
   {
      if(in->length + FF_INPUT_BUFFER_PADDING_SIZE <= in->alloc_size)
         memset(in->data + in->length, 0, FF_INPUT_BUFFER_PADDING_SIZE);
      else
         LOG_WARN("could not pad buffer"); // Try to decode the data anyway
   }

   /* The actual decoding */
   module->codec_context->reordered_opaque = in->pts;
   av_init_packet(&avpkt);
   avpkt.data = in->length ? in->data + in->offset : 0;
   avpkt.size = in->length;
   used = avcodec_decode_video2(module->codec_context, module->picture,
                                &module->picture_available, &avpkt);

   /* Check for errors */
   if (used < 0 || used > (int)in->length)
   {
      LOG_ERROR("decoding failed (%i), discarding buffer", used);
      used = in->length;
   }

   if (module->picture_available)
   {
      module->pts = module->picture->reordered_opaque;
      if (module->pts == MMAL_TIME_UNKNOWN)
         module->pts = in->dts;
   }

 end:
   in->offset += used;
   in->length -= used;

   if (in->length)
   {
      mmal_queue_put_back(module->queue_in, in);
      return 1;
   }

   /* We want to keep the EOS buffer until all the frames have been flushed */
   if ((in->flags & MMAL_BUFFER_HEADER_FLAG_EOS) &&
       module->picture_available)
   {
      mmal_queue_put_back(module->queue_in, in);
      return 1;
   }

   /* Send EOS */
   if ((in->flags & MMAL_BUFFER_HEADER_FLAG_EOS) &&
       avcodec_send_eos(component, port_out) != MMAL_SUCCESS)
   {
      mmal_queue_put_back(module->queue_in, in);
      return 0;
   }

   in->offset = 0;
   mmal_port_buffer_header_callback(port_in, in);
   return 1;
}