#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  size; TYPE_1__* priv; } ;
typedef  TYPE_2__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_17__ {int flags; scalar_t__ size; int /*<<< orphan*/  data; int /*<<< orphan*/  track; int /*<<< orphan*/  pts; int /*<<< orphan*/  dts; } ;
typedef  TYPE_3__ VC_CONTAINER_PACKET_T ;
struct TYPE_18__ {int /*<<< orphan*/  sample_offset; int /*<<< orphan*/  samples; int /*<<< orphan*/  tracks_add_done; TYPE_3__ sample; } ;
typedef  TYPE_4__ VC_CONTAINER_MODULE_T ;
struct TYPE_15__ {TYPE_4__* module; } ;

/* Variables and functions */
 int /*<<< orphan*/  STREAM_POSITION (TYPE_2__*) ; 
 scalar_t__ STREAM_STATUS (TYPE_2__*) ; 
 int VC_CONTAINER_PACKET_FLAG_FRAME_END ; 
 int VC_CONTAINER_PACKET_FLAG_FRAME_START ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 scalar_t__ WRITE_BYTES (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ mp4_writer_add_sample (TYPE_2__*,TYPE_3__*) ; 
 scalar_t__ mp4_writer_add_track_done (TYPE_2__*) ; 
 scalar_t__ mp4_writer_write_sample_to_temp (TYPE_2__*,TYPE_3__*) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mp4_writer_write( VC_CONTAINER_T *p_ctx,
                                               VC_CONTAINER_PACKET_T *packet )
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   VC_CONTAINER_PACKET_T *sample = &module->sample;
   VC_CONTAINER_STATUS_T status;

   if(!module->tracks_add_done)
   {
      status = mp4_writer_add_track_done(p_ctx);
      if(status != VC_CONTAINER_SUCCESS) return status;
   }

   if(packet->flags & VC_CONTAINER_PACKET_FLAG_FRAME_START)
      ++module->samples; /* Switching to a new sample */

   if(packet->flags & VC_CONTAINER_PACKET_FLAG_FRAME_START)
   {
      module->sample_offset = STREAM_POSITION(p_ctx);
      sample->size = packet->size;
      sample->pts = packet->pts;
      sample->dts = packet->pts;
      sample->track = packet->track;
      sample->flags = packet->flags;
   }
   else
   {
      sample->size += packet->size;
      sample->flags |= packet->flags;
   }

   if(WRITE_BYTES(p_ctx, packet->data, packet->size) != packet->size)
      return STREAM_STATUS(p_ctx); // TODO do something
   p_ctx->size += packet->size;

   //
   if(packet->flags & VC_CONTAINER_PACKET_FLAG_FRAME_END)
   {
      status = mp4_writer_write_sample_to_temp(p_ctx, sample);
      status = mp4_writer_add_sample(p_ctx, sample);
   }

   return VC_CONTAINER_SUCCESS;
}