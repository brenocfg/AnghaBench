#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  void* int64_t ;
struct TYPE_8__ {int tracks_num; } ;
typedef  TYPE_1__ VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_9__ {int data_offset; int data_size; int flags; int tag_prev_size; int track; int /*<<< orphan*/  status; int /*<<< orphan*/  timestamp; void* data_position; void* tag_position; } ;
typedef  TYPE_2__ FLV_READER_STATE_T ;

/* Variables and functions */
 void* STREAM_POSITION (TYPE_1__*) ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_CONTINUE ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  flv_read_frame_header (TYPE_1__*,int*,int*,int*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flv_validate_frame_data (TYPE_1__*,int,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T flv_read_sample_header( VC_CONTAINER_T *p_ctx,
   FLV_READER_STATE_T *state)
{
   int track, prev_size, size, flags;
   uint32_t timestamp;
   int64_t position;

   /* Check if we still have some data left to read from the current frame */
   if(state->data_offset < state->data_size)
      return state->status;

   /* Read the next tag header */
   position = STREAM_POSITION(p_ctx);
   state->status = flv_read_frame_header(p_ctx, &prev_size, &track,
                                         &size, &timestamp, &flags, 0);
   if(state->status != VC_CONTAINER_SUCCESS)
      return state->status;

   state->status = flv_validate_frame_data(p_ctx, track, &size, &timestamp);
   if(state->status == VC_CONTAINER_ERROR_CONTINUE)
   {
      /* Skip it */
      state->status = VC_CONTAINER_SUCCESS;
      track = p_ctx->tracks_num;
   }
   if(state->status != VC_CONTAINER_SUCCESS)
      return state->status;

   state->tag_position = position;
   state->data_position = STREAM_POSITION(p_ctx);
   state->data_size = size;
   state->data_offset = 0;
   state->flags = flags;
   state->tag_prev_size = prev_size;
   state->timestamp = timestamp;
   state->track = track;
   return state->status;
}