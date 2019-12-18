#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_20__ {int /*<<< orphan*/  is_enabled; TYPE_3__* priv; } ;
typedef  TYPE_5__ VC_CONTAINER_TRACK_T ;
struct TYPE_21__ {int tracks_num; TYPE_5__** tracks; TYPE_1__* priv; } ;
typedef  TYPE_6__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_22__ {size_t track; int size; int buffer_size; int /*<<< orphan*/  flags; int /*<<< orphan*/  data; int /*<<< orphan*/  pts; int /*<<< orphan*/  dts; } ;
typedef  TYPE_7__ VC_CONTAINER_PACKET_T ;
struct TYPE_24__ {int eos; int corrupted; int flags; size_t level; TYPE_4__* levels; int /*<<< orphan*/  pts; } ;
struct TYPE_23__ {TYPE_9__ state; } ;
typedef  TYPE_8__ VC_CONTAINER_MODULE_T ;
struct TYPE_19__ {int /*<<< orphan*/  data_offset; } ;
struct TYPE_18__ {TYPE_2__* module; } ;
struct TYPE_17__ {TYPE_9__* state; } ;
struct TYPE_16__ {TYPE_8__* module; } ;
typedef  TYPE_9__ MKV_READER_STATE_T ;

/* Variables and functions */
 scalar_t__ VC_CONTAINER_ERROR_CONTINUE ; 
 scalar_t__ VC_CONTAINER_ERROR_CORRUPTED ; 
 scalar_t__ VC_CONTAINER_ERROR_EOS ; 
 int /*<<< orphan*/  VC_CONTAINER_PACKET_FLAG_FRAME_END ; 
 int /*<<< orphan*/  VC_CONTAINER_PACKET_FLAG_FRAME_START ; 
 int /*<<< orphan*/  VC_CONTAINER_PACKET_FLAG_KEYFRAME ; 
 int VC_CONTAINER_READ_FLAG_FORCE_TRACK ; 
 int VC_CONTAINER_READ_FLAG_INFO ; 
 int VC_CONTAINER_READ_FLAG_SKIP ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 scalar_t__ mkv_read_frame_data (TYPE_6__*,TYPE_9__*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ mkv_read_next_frame_header (TYPE_6__*,TYPE_9__*,int*,int*) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mkv_reader_read(VC_CONTAINER_T *p_ctx,
   VC_CONTAINER_PACKET_T *p_packet, uint32_t flags)
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   VC_CONTAINER_TRACK_T *p_track = 0;
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;
   uint32_t buffer_size = 0, track = 0, data_size;
   MKV_READER_STATE_T *state = &module->state;

   /* If a specific track has been selected, we need to use the track packet state */
   if(flags & VC_CONTAINER_READ_FLAG_FORCE_TRACK)
   {
      p_track = p_ctx->tracks[p_packet->track];
      state = p_track->priv->module->state;
   }

   /**/
   if(state->eos) return VC_CONTAINER_ERROR_EOS;
   if(state->corrupted) return VC_CONTAINER_ERROR_CORRUPTED;

   /* Look at the next frame header */
   status = mkv_read_next_frame_header(p_ctx, state, &track, &data_size);
   if(status == VC_CONTAINER_ERROR_EOS) state->eos = true;
   if(status == VC_CONTAINER_ERROR_CORRUPTED) state->corrupted = true;
   if(status != VC_CONTAINER_SUCCESS) return status;

   if(track >= p_ctx->tracks_num || !p_ctx->tracks[track]->is_enabled)
   {
      /* Skip frame */
      status = mkv_read_frame_data(p_ctx, state, 0, &data_size);
      if (status != VC_CONTAINER_SUCCESS) return status;
      return VC_CONTAINER_ERROR_CONTINUE;
   }

   if((flags & VC_CONTAINER_READ_FLAG_SKIP) && !(flags & VC_CONTAINER_READ_FLAG_INFO)) /* Skip packet */
      return mkv_read_frame_data(p_ctx, state, 0, &data_size);

   p_packet->dts = p_packet->pts = state->pts;
   p_packet->flags = 0;
   if(state->flags & 0x80) p_packet->flags |= VC_CONTAINER_PACKET_FLAG_KEYFRAME;
   if(!state->levels[state->level].data_offset) p_packet->flags |= VC_CONTAINER_PACKET_FLAG_FRAME_START;
   p_packet->flags |= VC_CONTAINER_PACKET_FLAG_FRAME_END;
   p_packet->size = data_size;
   p_packet->track = track;

   if(flags & VC_CONTAINER_READ_FLAG_SKIP)
      return mkv_read_frame_data(p_ctx, state, 0, &data_size );
   else if(flags & VC_CONTAINER_READ_FLAG_INFO)
      return VC_CONTAINER_SUCCESS;

   /* Read the frame data */
   buffer_size = p_packet->buffer_size;
   status = mkv_read_frame_data(p_ctx, state, p_packet->data, &buffer_size);
   if(status != VC_CONTAINER_SUCCESS)
   {
      /* FIXME */
      return status;
   }

   p_packet->size = buffer_size;
   if(buffer_size != data_size)
      p_packet->flags &= ~VC_CONTAINER_PACKET_FLAG_FRAME_END;

   return status;
}