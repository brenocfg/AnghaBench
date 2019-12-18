#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint32_t ;
struct TYPE_13__ {TYPE_2__** tracks; } ;
typedef  TYPE_3__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_14__ {int stream_num; int /*<<< orphan*/  media_object_off; } ;
struct TYPE_12__ {TYPE_1__* format; } ;
struct TYPE_11__ {scalar_t__ es_type; } ;
typedef  TYPE_4__ ASF_PACKET_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  ASF_MAX_SEARCH_PACKETS ; 
 scalar_t__ VC_CONTAINER_ES_TYPE_VIDEO ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 scalar_t__ asf_read_next_payload (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ ,unsigned int*) ; 
 scalar_t__ asf_read_next_payload_header (TYPE_3__*,TYPE_4__*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T asf_reader_find_next_frame( VC_CONTAINER_T *p_ctx,
   unsigned int track, ASF_PACKET_STATE *p_state, bool keyframe, bool timeout )
{
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;
   uint32_t data_track, data_size;
   unsigned int packets = 0;

   if(p_ctx->tracks[track]->format->es_type != VC_CONTAINER_ES_TYPE_VIDEO)
      keyframe = false;

   /* We still need to go to the right payload */
   while(status == VC_CONTAINER_SUCCESS &&
         (!timeout || packets++ < ASF_MAX_SEARCH_PACKETS))
   {
      status = asf_read_next_payload_header( p_ctx, p_state, &data_track, &data_size );
      if(status != VC_CONTAINER_SUCCESS) break;

      if(data_track == track && ((p_state->stream_num >> 7) || !keyframe) &&
         !p_state->media_object_off) break;

      /* Skip payload */
      status = asf_read_next_payload(p_ctx, p_state, 0, &data_size );
   }

   return status;
}