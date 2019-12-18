#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int int64_t ;
struct TYPE_20__ {unsigned int tracks_num; TYPE_5__** tracks; TYPE_1__* priv; } ;
typedef  TYPE_6__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_SEEK_MODE_T ;
typedef  int VC_CONTAINER_SEEK_FLAGS_T ;
struct TYPE_21__ {scalar_t__ data_offset; } ;
typedef  TYPE_7__ VC_CONTAINER_MODULE_T ;
struct TYPE_22__ {int timestamp; int data_offset; scalar_t__ data_position; scalar_t__ tag_position; scalar_t__ status; scalar_t__ index; int /*<<< orphan*/  member_0; } ;
struct TYPE_19__ {TYPE_4__* priv; TYPE_2__* format; } ;
struct TYPE_18__ {TYPE_3__* module; } ;
struct TYPE_17__ {TYPE_8__* state; } ;
struct TYPE_16__ {scalar_t__ es_type; } ;
struct TYPE_15__ {TYPE_7__* module; } ;
typedef  TYPE_8__ FLV_READER_STATE_T ;

/* Variables and functions */
 int INT64_C (int) ; 
 int /*<<< orphan*/  LOG_DEBUG (TYPE_6__*,char*,int,...) ; 
 scalar_t__ SEEK (TYPE_6__*,scalar_t__) ; 
 scalar_t__ VC_CONTAINER_ERROR_CORRUPTED ; 
 scalar_t__ VC_CONTAINER_ES_TYPE_VIDEO ; 
 int /*<<< orphan*/  VC_CONTAINER_PARAM_UNUSED (int /*<<< orphan*/ ) ; 
 int VC_CONTAINER_SEEK_FLAG_FORWARD ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 scalar_t__ flv_find_next_frame (TYPE_6__*,unsigned int,int*,int*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ flv_find_previous_frame (TYPE_6__*,unsigned int,int*,int*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flv_update_track_position (TYPE_6__*,unsigned int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ vc_container_index_get (scalar_t__,int,int*,int*,int*) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T flv_reader_seek(VC_CONTAINER_T *p_ctx,
   int64_t *offset, VC_CONTAINER_SEEK_MODE_T mode, VC_CONTAINER_SEEK_FLAGS_T flags)
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;
   FLV_READER_STATE_T last_state = {0};
   FLV_READER_STATE_T *state;
   uint32_t time = (*offset / 1000), timestamp, previous_time;
   unsigned int i, track;
   int size, past = 0;
   int64_t position;
   VC_CONTAINER_PARAM_UNUSED(mode);

   /* If we have a video track, then we want to find the keyframe closest to
    * the requested time, otherwise we just look for the tag with the
    * closest timestamp */

   /* Select the track on which we'll do our seeking */
   for(i = 0, track = 0; i < p_ctx->tracks_num; i++)
   {
      if(p_ctx->tracks[i]->format->es_type != VC_CONTAINER_ES_TYPE_VIDEO) continue;
      track = i;
      break;
   }
   if(track >= p_ctx->tracks_num) return VC_CONTAINER_ERROR_CORRUPTED;
   state = p_ctx->tracks[track]->priv->module->state;
   previous_time = state->timestamp;

   LOG_DEBUG(p_ctx, "seek (%i, prev %i)", time, previous_time);

   if(state->index && vc_container_index_get(state->index, flags & VC_CONTAINER_SEEK_FLAG_FORWARD,
                                             offset, &position, &past) == VC_CONTAINER_SUCCESS)
   {
      flv_update_track_position(p_ctx, track, position, 0, position, 0, (uint32_t) (*offset / 1000LL), 0);
   }
   else
   {
      if(time < state->timestamp / 2)
         flv_update_track_position(p_ctx, track, (int64_t)module->data_offset, 0,
                                   (int64_t)module->data_offset, 0, 0, 0);
      past = 1;
   }

   /* If past it clear then we're done, otherwise we need to find our point from here */
   if(past == 0)
   {
      status = flv_find_next_frame(p_ctx, track, &size, &timestamp, 0, 1 /*keyframe*/, 0);
   }
   else
   {
      if(time > previous_time)
      {
         while(!status)
         {
            status = flv_find_next_frame(p_ctx, track, &size, &timestamp, 0, 1 /*keyframe*/, 0);
            if(status) break;

            /* Check if we have our frame */
            if(time <= timestamp) break;

            last_state = *state;
            state->data_offset = size; /* consume data */
         }
      }
      else
      {
         while(!status)
         {
            status = flv_find_previous_frame(p_ctx, track, &size, &timestamp, 0, 1 /*keyframe*/, 0);
            if(status) break;

            /* Check if we have our frame */
            if(time >= timestamp) break;

            /* Detect when we've reached the 1st keyframe to avoid an infinite loop */
            if(state->timestamp == last_state.timestamp) break;

            last_state = *state;
            state->data_offset = size; /* consume data */
         }
      }
   }

   if(status != VC_CONTAINER_SUCCESS && (flags & VC_CONTAINER_SEEK_FLAG_FORWARD))
   {
      LOG_DEBUG(p_ctx, "seek failed (%i)", status);
      return status;
   }
   else if(status != VC_CONTAINER_SUCCESS)
   {
      LOG_DEBUG(p_ctx, "seek failed (%i), look for previous frame", status);
      if(last_state.tag_position) *state = last_state;
      else status = flv_find_previous_frame(p_ctx, track, &size, &timestamp, 0, 1 /*keyframe*/, 0);
   }

   LOG_DEBUG(p_ctx, "seek done (%i)", timestamp);
   state->status = VC_CONTAINER_SUCCESS;
   last_state.status = VC_CONTAINER_SUCCESS;

   if(past == 1)
   {
      /* Make adjustment based on seek mode */
      if((flags & VC_CONTAINER_SEEK_FLAG_FORWARD) && timestamp < time && timestamp < previous_time)
      {
         if(last_state.tag_position) *state = last_state;
         else status = flv_find_next_frame(p_ctx, track, &size, &timestamp, 0, 1 /*keyframe*/, 0);
      }
      else if(!(flags & VC_CONTAINER_SEEK_FLAG_FORWARD) && timestamp > time)
      {
         if(last_state.tag_position) *state = last_state;
         else status = flv_find_previous_frame(p_ctx, track, &size, &timestamp, 0, 1 /*keyframe*/, 0);
      }

      LOG_DEBUG(p_ctx, "seek adjustment (%i)", timestamp);
   }

   if(state->data_position == last_state.data_position)
      status = SEEK(p_ctx, state->data_position);

   *offset = timestamp * INT64_C(1000);

   return VC_CONTAINER_SUCCESS;
}