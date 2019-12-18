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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_16__ {TYPE_1__* priv; } ;
typedef  TYPE_2__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_17__ {int object_level; scalar_t__* stream_number_to_index; } ;
typedef  TYPE_3__ VC_CONTAINER_MODULE_T ;
struct TYPE_18__ {scalar_t__ subpayload_size; scalar_t__ current_payload; scalar_t__ num_payloads; scalar_t__ size; scalar_t__ start; scalar_t__ payload_size; scalar_t__ media_object_size; int stream_num; scalar_t__ current_offset; scalar_t__ media_object_pts_delta; int /*<<< orphan*/  media_object_pts; scalar_t__ media_object_off; scalar_t__ compressed_payloads; } ;
struct TYPE_15__ {TYPE_3__* module; } ;
typedef  TYPE_4__ ASF_PACKET_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG (TYPE_2__*,char*) ; 
 scalar_t__ READ_U8 (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  SKIP_BYTES (TYPE_2__*,scalar_t__) ; 
 scalar_t__ STREAM_POSITION (TYPE_2__*) ; 
 scalar_t__ VC_CONTAINER_ERROR_CORRUPTED ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 scalar_t__ asf_read_packet_header (TYPE_2__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ asf_read_payload_header (TYPE_2__*,TYPE_4__*) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T asf_read_next_payload_header( VC_CONTAINER_T *p_ctx,
   ASF_PACKET_STATE *p_state, uint32_t *pi_track, uint32_t *pi_length)
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   VC_CONTAINER_STATUS_T status;

   if(p_state->subpayload_size)
   {
      /* We still haven't read the current subpayload, return the info we already have */
      goto end;
   }

   /* Check if we're done reading a packet */
   if(p_state->current_payload >= p_state->num_payloads)
   {
      /* Skip the padding at the end */
      if(p_state->size)
      {
         int32_t pad_length = p_state->size - (STREAM_POSITION(p_ctx) - p_state->start);
         if(pad_length < 0) return VC_CONTAINER_ERROR_CORRUPTED;
         SKIP_BYTES(p_ctx, pad_length); /* Padding */
      }

      /* Read the header for the next packet */
      module->object_level = 0; /* For debugging */
      status = asf_read_packet_header( p_ctx, p_state, (uint64_t)0/*size???*/ );
      module->object_level = 1; /* For debugging */
      if(status != VC_CONTAINER_SUCCESS) return status;
   }

   /* Check if we're done reading a payload */
   if(!p_state->payload_size)
   {
      /* Read the payload header */
      status = asf_read_payload_header( p_ctx, p_state );
      if(status != VC_CONTAINER_SUCCESS) return status;
   }

   /* For compressed payloads, payload_size != subpayload_size */
   if(p_state->compressed_payloads && p_state->payload_size)
   {
      p_state->payload_size--;
      p_state->subpayload_size = READ_U8(p_ctx, "Sub-Payload Data Length");
      if(p_state->subpayload_size > p_state->payload_size)
      {
         /* TODO: do something ? */
         LOG_DEBUG(p_ctx, "subpayload is too big");
         p_state->subpayload_size = p_state->payload_size;
      }
      p_state->media_object_off = 0;
      p_state->media_object_size = p_state->subpayload_size;
      p_state->media_object_pts += p_state->media_object_pts_delta;
   }

 end:
   /* We've read the payload header, return the requested info */
   if(pi_track) *pi_track = module->stream_number_to_index[p_state->stream_num & 0x7F];
   if(pi_length) *pi_length = p_state->subpayload_size;

   p_state->current_offset = STREAM_POSITION(p_ctx) - p_state->start;
   return VC_CONTAINER_SUCCESS;
}