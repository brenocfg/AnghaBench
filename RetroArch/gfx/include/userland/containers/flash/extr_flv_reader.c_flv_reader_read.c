#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int int64_t ;
struct TYPE_16__ {size_t tracks_num; TYPE_2__** tracks; TYPE_1__* priv; } ;
typedef  TYPE_3__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_17__ {int dts; int pts; size_t track; unsigned int frame_size; unsigned int size; unsigned int buffer_size; int /*<<< orphan*/  flags; int /*<<< orphan*/  data; } ;
typedef  TYPE_4__ VC_CONTAINER_PACKET_T ;
struct TYPE_19__ {int timestamp; int flags; unsigned int data_offset; unsigned int data_size; size_t track; scalar_t__ tag_position; scalar_t__ data_position; } ;
struct TYPE_18__ {TYPE_6__ state; } ;
typedef  TYPE_5__ VC_CONTAINER_MODULE_T ;
struct TYPE_15__ {int /*<<< orphan*/  is_enabled; } ;
struct TYPE_14__ {TYPE_5__* module; } ;
typedef  TYPE_6__ FLV_READER_STATE_T ;

/* Variables and functions */
 int FLV_FLAG_KEYFRAME ; 
 int /*<<< orphan*/  LOG_DEBUG (TYPE_3__*,char*,int,int,int,int,unsigned int,unsigned int) ; 
 scalar_t__ VC_CONTAINER_ERROR_CONTINUE ; 
 int /*<<< orphan*/  VC_CONTAINER_PACKET_FLAG_FRAME_END ; 
 int /*<<< orphan*/  VC_CONTAINER_PACKET_FLAG_FRAME_START ; 
 int /*<<< orphan*/  VC_CONTAINER_PACKET_FLAG_KEYFRAME ; 
 int VC_CONTAINER_READ_FLAG_INFO ; 
 int VC_CONTAINER_READ_FLAG_SKIP ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 scalar_t__ flv_read_sample_data (TYPE_3__*,TYPE_6__*,int /*<<< orphan*/ ,unsigned int*) ; 
 scalar_t__ flv_read_sample_header (TYPE_3__*,TYPE_6__*) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T flv_reader_read( VC_CONTAINER_T *p_ctx,
   VC_CONTAINER_PACKET_T *packet, uint32_t flags )
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;
   FLV_READER_STATE_T *state = &module->state;
   unsigned int data_size;

   /* TODO: select right state */

   status = flv_read_sample_header(p_ctx, state);
   if(status != VC_CONTAINER_SUCCESS) return status;

#ifdef ENABLE_FLV_EXTRA_LOGGING
   LOG_DEBUG(p_ctx, "read_sample_header (%i,%i,%i/%i/%i/%i)", state->timestamp, state->flags,
         (int)state->tag_position, (int)(state->data_position-state->tag_position), state->data_offset, state->data_size);
#endif

   if(state->track >= p_ctx->tracks_num || !p_ctx->tracks[state->track]->is_enabled)
   {
      /* Skip packet */
      status = flv_read_sample_data(p_ctx, state, 0, 0);
      if(status != VC_CONTAINER_SUCCESS) return status;
      return VC_CONTAINER_ERROR_CONTINUE;
   }

   if((flags & VC_CONTAINER_READ_FLAG_SKIP) && !(flags & VC_CONTAINER_READ_FLAG_INFO)) /* Skip packet */
      return flv_read_sample_data(p_ctx, state, 0, 0);

   packet->dts = packet->pts = state->timestamp * (int64_t)1000;
   packet->flags = VC_CONTAINER_PACKET_FLAG_FRAME_END;
   if(state->flags & FLV_FLAG_KEYFRAME) packet->flags |= VC_CONTAINER_PACKET_FLAG_KEYFRAME;
   if(!state->data_offset) packet->flags |= VC_CONTAINER_PACKET_FLAG_FRAME_START;
   packet->track = state->track;

   // The frame size is all the data
   packet->frame_size = state->data_size;

   // the size is what's left
   packet->size = state->data_size - state->data_offset;

   if(flags & VC_CONTAINER_READ_FLAG_SKIP)
      return flv_read_sample_data(p_ctx, state, 0, 0);
   else if(flags & VC_CONTAINER_READ_FLAG_INFO)
      return VC_CONTAINER_SUCCESS;

   data_size = packet->buffer_size;
   status = flv_read_sample_data(p_ctx, state, packet->data, &data_size);
   if(status != VC_CONTAINER_SUCCESS)
   {
      /* FIXME */
      return status;
   }

   packet->size = data_size;
   if(state->data_offset != state->data_size)
      packet->flags &= ~VC_CONTAINER_PACKET_FLAG_FRAME_END;

   return VC_CONTAINER_SUCCESS;
}