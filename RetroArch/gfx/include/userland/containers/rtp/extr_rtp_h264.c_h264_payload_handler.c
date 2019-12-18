#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_10__ {TYPE_1__* priv; } ;
typedef  TYPE_2__ VC_CONTAINER_TRACK_T ;
struct TYPE_11__ {int /*<<< orphan*/  flags; scalar_t__ extra; int /*<<< orphan*/  payload; } ;
typedef  TYPE_3__ VC_CONTAINER_TRACK_MODULE_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_12__ {int* data; int buffer_size; int size; int flags; } ;
typedef  TYPE_4__ VC_CONTAINER_PACKET_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_BITS_T ;
struct TYPE_13__ {int nal_unit_size; int header_bytes_to_write; int nal_header; int /*<<< orphan*/  flags; } ;
struct TYPE_9__ {TYPE_3__* module; } ;
typedef  TYPE_5__ H264_PAYLOAD_T ;

/* Variables and functions */
 scalar_t__ BITS_BYTES_AVAILABLE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BITS_COPY_BYTES (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int*,char*) ; 
 int BITS_READ_U32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  BITS_SKIP_BYTES (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*) ; 
 scalar_t__ BIT_IS_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLEAR_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  H264F_NEXT_PACKET_IS_START ; 
 int /*<<< orphan*/  LOG_ERROR (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SET_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACK_HAS_MARKER ; 
 int /*<<< orphan*/  TRACK_NEW_PACKET ; 
 scalar_t__ VC_CONTAINER_ERROR_FORMAT_INVALID ; 
 int VC_CONTAINER_PACKET_FLAG_FRAME_END ; 
 int VC_CONTAINER_PACKET_FLAG_FRAME_START ; 
 int VC_CONTAINER_READ_FLAG_INFO ; 
 int VC_CONTAINER_READ_FLAG_SKIP ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 scalar_t__ h264_new_rtp_packet (int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T h264_payload_handler(VC_CONTAINER_T *p_ctx,
      VC_CONTAINER_TRACK_T *track,
      VC_CONTAINER_PACKET_T *p_packet,
      uint32_t flags)
{
   VC_CONTAINER_TRACK_MODULE_T *t_module = track->priv->module;
   VC_CONTAINER_BITS_T *payload = &t_module->payload;
   H264_PAYLOAD_T *extra = (H264_PAYLOAD_T *)t_module->extra;
   uint32_t packet_flags = 0;
   uint8_t header_bytes_to_write;
   uint32_t size, offset;
   uint8_t *data_ptr;
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;
   bool last_nal_unit_in_packet = false;

   if (BIT_IS_SET(t_module->flags, TRACK_NEW_PACKET))
   {
      status = h264_new_rtp_packet(p_ctx, t_module);
      if (status != VC_CONTAINER_SUCCESS)
         return status;
   }

   if (BIT_IS_SET(extra->flags, H264F_NEXT_PACKET_IS_START))
   {
      packet_flags |= VC_CONTAINER_PACKET_FLAG_FRAME_START;

      if (!(flags & VC_CONTAINER_READ_FLAG_INFO))
         CLEAR_BIT(extra->flags, H264F_NEXT_PACKET_IS_START);
   }

   if (!extra->nal_unit_size && BITS_BYTES_AVAILABLE(p_ctx, payload))
   {
      uint32_t stap_unit_header;

      /* STAP-A packet: read NAL unit size and header from payload */
      stap_unit_header = BITS_READ_U32(p_ctx, payload, 24, "STAP unit header");
      extra->nal_unit_size = stap_unit_header >> 8;
      if (extra->nal_unit_size > BITS_BYTES_AVAILABLE(p_ctx, payload))
      {
         LOG_ERROR(p_ctx, "H.264: STAP-A NAL unit size bigger than payload");
         return VC_CONTAINER_ERROR_FORMAT_INVALID;
      }
      extra->header_bytes_to_write = 5;
      extra->nal_header = (uint8_t)stap_unit_header;
   }

   header_bytes_to_write = extra->header_bytes_to_write;
   size = extra->nal_unit_size + header_bytes_to_write;

   if (p_packet && !(flags & VC_CONTAINER_READ_FLAG_SKIP))
   {
      if (flags & VC_CONTAINER_READ_FLAG_INFO)
      {
         /* In order to set the frame end flag correctly, need to work out if this
          * is the only NAL unit or last in an aggregated packet */
         last_nal_unit_in_packet = (extra->nal_unit_size == BITS_BYTES_AVAILABLE(p_ctx, payload));
      } else {
         offset = 0;
         data_ptr = p_packet->data;

         if (size > p_packet->buffer_size)
         {
            /* Buffer not big enough */
            size = p_packet->buffer_size;
         }

         /* Insert start code and header into the data stream */
         while (offset < size && header_bytes_to_write)
         {
            uint8_t header_byte;

            switch (header_bytes_to_write)
            {
            case 2: header_byte = 0x01; break;
            case 1: header_byte = extra->nal_header; break;
            default: header_byte = 0x00;
            }
            data_ptr[offset++] = header_byte;
            header_bytes_to_write--;
         }
         extra->header_bytes_to_write = header_bytes_to_write;

         if (offset < size)
         {
            BITS_COPY_BYTES(p_ctx, payload, size - offset, data_ptr + offset, "Packet data");
            extra->nal_unit_size -= (size - offset);
         }

         /* If we've read the final bytes of the packet, this must be the last (or only)
          * NAL unit in it */
         last_nal_unit_in_packet = !BITS_BYTES_AVAILABLE(p_ctx, payload);
      }
      p_packet->size = size;
   } else {
      extra->header_bytes_to_write = 0;
      BITS_SKIP_BYTES(p_ctx, payload, extra->nal_unit_size, "Packet data");
      last_nal_unit_in_packet = !BITS_BYTES_AVAILABLE(p_ctx, payload);
      extra->nal_unit_size = 0;
   }

   /* The marker bit on an RTP packet indicates the frame ends at the end of packet */
   if (last_nal_unit_in_packet && BIT_IS_SET(t_module->flags, TRACK_HAS_MARKER))
   {
      packet_flags |= VC_CONTAINER_PACKET_FLAG_FRAME_END;

      /* If this was the last packet of a frame, the next one must be the start */
      if (!(flags & VC_CONTAINER_READ_FLAG_INFO))
         SET_BIT(extra->flags, H264F_NEXT_PACKET_IS_START);
   }

   if (p_packet)
      p_packet->flags = packet_flags;

   return status;
}