#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {int timestamp; int payload_type; int expected_ssrc; int timestamp_base; int /*<<< orphan*/  flags; int /*<<< orphan*/  payload; } ;
typedef  TYPE_1__ VC_CONTAINER_TRACK_MODULE_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_BITS_T ;

/* Variables and functions */
 int BITS_BYTES_AVAILABLE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BITS_COPY_STREAM (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BITS_INVALIDATE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BITS_READ_U16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*) ; 
 int BITS_READ_U32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  BITS_READ_U8 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  BITS_REDUCE_BYTES (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BITS_SKIP (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  BITS_SKIP_BYTES (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  BITS_VALID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ BIT_IS_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLEAR_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_DEBUG (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  SET_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACK_HAS_MARKER ; 
 int /*<<< orphan*/  TRACK_SSRC_SET ; 
 int /*<<< orphan*/  update_sequence_number (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void decode_rtp_packet_header(VC_CONTAINER_T *p_ctx,
      VC_CONTAINER_TRACK_MODULE_T *t_module)
{
   VC_CONTAINER_BITS_T *payload = &t_module->payload;
   uint32_t version, has_padding, has_extension, csrc_count, has_marker;
   uint32_t payload_type, ssrc;
   uint16_t seq_num;

   /* Break down fixed header area into component parts */
   version              = BITS_READ_U32(p_ctx, payload, 2, "Version");
   has_padding          = BITS_READ_U32(p_ctx, payload, 1, "Has padding");
   has_extension        = BITS_READ_U32(p_ctx, payload, 1, "Has extension");
   csrc_count           = BITS_READ_U32(p_ctx, payload, 4, "CSRC count");
   has_marker           = BITS_READ_U32(p_ctx, payload, 1, "Has marker");
   payload_type         = BITS_READ_U32(p_ctx, payload, 7, "Payload type");
   seq_num              = BITS_READ_U16(p_ctx, payload, 16, "Sequence number");
   t_module->timestamp  = BITS_READ_U32(p_ctx, payload, 32, "Timestamp");
   ssrc                 = BITS_READ_U32(p_ctx, payload, 32, "SSRC");

   /* If there was only a partial header, abort immediately */
   if (!BITS_VALID(p_ctx, payload))
      return;

   /* Validate version, payload type, sequence number and SSRC, if set */
   if (version != 2 || payload_type != t_module->payload_type)
   {
      BITS_INVALIDATE(p_ctx, payload);
      return;
   }
   if (BIT_IS_SET(t_module->flags, TRACK_SSRC_SET) && (ssrc != t_module->expected_ssrc))
   {
      LOG_DEBUG(p_ctx, "RTP: Unexpected SSRC (0x%8.8X)", ssrc);
      BITS_INVALIDATE(p_ctx, payload);
      return;
   }

   /* Check sequence number indicates packet is usable */
   if (!update_sequence_number(t_module, seq_num))
   {
      BITS_INVALIDATE(p_ctx, payload);
      return;
   }

   /* Adjust to account for padding, CSRCs and extension */
   if (has_padding)
   {
      VC_CONTAINER_BITS_T bit_stream;
      uint32_t available = BITS_BYTES_AVAILABLE(p_ctx, payload);
      uint8_t padding;

      BITS_COPY_STREAM(p_ctx, &bit_stream, payload);
      /* The last byte of the payload is the number of padding bytes, including itself */
      BITS_SKIP_BYTES(p_ctx, &bit_stream, available - 1, "Skip to padding length");
      padding = BITS_READ_U8(p_ctx, &bit_stream, 8, "Padding length");

      BITS_REDUCE_BYTES(p_ctx, payload, padding, "Remove padding");
   }

   /* Each CSRC is 32 bits, so shift count up to skip the right number of bits */
   BITS_SKIP(p_ctx, payload, csrc_count << 5, "CSRC section");

   if (has_extension)
   {
      uint32_t extension_bits;

      /* Extension header is 16-bit ID (which isn't needed), then 16-bit length in 32-bit words */
      BITS_SKIP(p_ctx, payload, 16, "Extension ID");
      extension_bits = BITS_READ_U32(p_ctx, payload, 16, "Extension length") << 5;
      BITS_SKIP(p_ctx, payload, extension_bits, "Extension data");
   }

   /* Record whether or not this RTP packet had the marker bit set */
   if (has_marker)
      SET_BIT(t_module->flags, TRACK_HAS_MARKER);
   else
      CLEAR_BIT(t_module->flags, TRACK_HAS_MARKER);

   /* If it hasn't been set independently, use the first timestamp as a baseline */
   if (!t_module->timestamp_base)
      t_module->timestamp_base = t_module->timestamp;
   t_module->timestamp -= t_module->timestamp_base;
}