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

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_21__ {TYPE_5__** tracks; TYPE_1__* priv; } ;
typedef  TYPE_6__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_22__ {scalar_t__ data_offset; } ;
typedef  TYPE_7__ VC_CONTAINER_MODULE_T ;
struct TYPE_23__ {scalar_t__ tag_position; scalar_t__ tag_prev_size; int data_offset; } ;
struct TYPE_20__ {TYPE_4__* format; TYPE_3__* priv; } ;
struct TYPE_19__ {scalar_t__ es_type; } ;
struct TYPE_18__ {TYPE_2__* module; } ;
struct TYPE_17__ {TYPE_8__* state; } ;
struct TYPE_16__ {TYPE_7__* module; } ;
typedef  TYPE_8__ FLV_READER_STATE_T ;

/* Variables and functions */
 int FLV_FLAG_DISCARD ; 
 int FLV_FLAG_KEYFRAME ; 
 scalar_t__ SEEK (TYPE_6__*,scalar_t__) ; 
 scalar_t__ STREAM_POSITION (TYPE_6__*) ; 
 scalar_t__ VC_CONTAINER_ES_TYPE_VIDEO ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 scalar_t__ flv_find_next_frame (TYPE_6__*,int,int*,scalar_t__*,int*,int,int) ; 
 scalar_t__ flv_read_frame_header (TYPE_6__*,int*,int*,int*,scalar_t__*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flv_update_track_position (TYPE_6__*,int,scalar_t__,int,scalar_t__,int,scalar_t__,int) ; 
 scalar_t__ flv_validate_frame_data (TYPE_6__*,int,int*,scalar_t__*) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T flv_find_previous_frame(VC_CONTAINER_T *p_ctx, int track, int *p_size,
   uint32_t *p_timestamp, int *p_flags, int b_keyframe, int b_extra_check)
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   FLV_READER_STATE_T *state = p_ctx->tracks[track]->priv->module->state;
   int frame_track, prev_size, size, flags;
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;
   uint32_t timestamp;
   int64_t position;

   /* Look for the previous frame we want */
   while (status == VC_CONTAINER_SUCCESS)
   {
      /* Seek to the previous tag in the stream */
      position = state->tag_position - state->tag_prev_size;
      if(position < module->data_offset) position = module->data_offset;
      status = SEEK(p_ctx, position);
      if(status != VC_CONTAINER_SUCCESS) return status;

      status = flv_read_frame_header(p_ctx, &prev_size, &frame_track,
                                     &size, &timestamp, &flags, 0);
      if(status) break;

      if(flags & FLV_FLAG_DISCARD) goto skip;
      if(frame_track != track) goto skip;

      if(b_keyframe && p_ctx->tracks[track]->format->es_type == VC_CONTAINER_ES_TYPE_VIDEO &&
         !(flags & FLV_FLAG_KEYFRAME)) goto skip;

      if(flv_validate_frame_data(p_ctx, track, &size, &timestamp) != VC_CONTAINER_SUCCESS)
         goto skip;

      /* We have what we need */
      flv_update_track_position(p_ctx, track, position, prev_size, STREAM_POSITION(p_ctx),
                                size, timestamp, flags);
      break;

   skip:
      if(position <= module->data_offset)
      {
         /* We're back at the beginning but we still want to return something */
         flv_update_track_position(p_ctx, track, (int64_t)module->data_offset, 0,
                                   (int64_t)module->data_offset, 0, 0, 0);
         return flv_find_next_frame(p_ctx, track, p_size, p_timestamp, p_flags, b_keyframe, b_extra_check);
      }
      flv_update_track_position(p_ctx, track, position, prev_size, STREAM_POSITION(p_ctx),
                                size, timestamp, 0);
      state->data_offset = size; /* consume data */
   }

   if(!status)
   {
      if(p_size) *p_size = size;
      if(p_timestamp) *p_timestamp = timestamp;
      if(p_flags) *p_flags = flags;
   }
   return status;
}