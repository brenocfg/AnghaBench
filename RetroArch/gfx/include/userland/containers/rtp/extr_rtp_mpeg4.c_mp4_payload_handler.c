#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_12__ {TYPE_1__* priv; } ;
typedef  TYPE_2__ VC_CONTAINER_TRACK_T ;
struct TYPE_13__ {int /*<<< orphan*/  flags; scalar_t__ extra; int /*<<< orphan*/  payload; } ;
typedef  TYPE_3__ VC_CONTAINER_TRACK_MODULE_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_14__ {scalar_t__ buffer_size; scalar_t__ size; int /*<<< orphan*/  data; int /*<<< orphan*/  dts; int /*<<< orphan*/  pts; } ;
typedef  TYPE_4__ VC_CONTAINER_PACKET_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_BITS_T ;
struct TYPE_16__ {scalar_t__ available; scalar_t__ dts_delta; scalar_t__ cts_delta; } ;
struct TYPE_15__ {TYPE_6__ au_info; } ;
struct TYPE_11__ {TYPE_3__* module; } ;
typedef  TYPE_5__ MP4_PAYLOAD_T ;
typedef  TYPE_6__ AU_INFO_T ;

/* Variables and functions */
 scalar_t__ BITS_BYTES_AVAILABLE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BITS_COPY_BYTES (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BITS_SKIP_BYTES (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,char*) ; 
 scalar_t__ BITS_VALID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int BIT_IS_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACK_NEW_PACKET ; 
 scalar_t__ VC_CONTAINER_ERROR_FORMAT_INVALID ; 
 scalar_t__ VC_CONTAINER_READ_FLAG_INFO ; 
 scalar_t__ VC_CONTAINER_READ_FLAG_SKIP ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 scalar_t__ mp4_new_rtp_packet (int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ mp4_next_au_header (int /*<<< orphan*/ *,TYPE_5__*,int) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mp4_payload_handler(VC_CONTAINER_T *p_ctx,
      VC_CONTAINER_TRACK_T *track,
      VC_CONTAINER_PACKET_T *p_packet,
      uint32_t flags)
{
   VC_CONTAINER_TRACK_MODULE_T *t_module = track->priv->module;
   VC_CONTAINER_BITS_T *payload = &t_module->payload;
   MP4_PAYLOAD_T *extra = (MP4_PAYLOAD_T *)t_module->extra;
   AU_INFO_T *au_info = &extra->au_info;
   bool is_new_packet = BIT_IS_SET(t_module->flags, TRACK_NEW_PACKET);
   uint32_t bytes_left_in_payload;
   uint32_t size;
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;

   if (is_new_packet)
   {
      status = mp4_new_rtp_packet(p_ctx, t_module);
      if (status != VC_CONTAINER_SUCCESS)
         return status;
   }

   if (!au_info->available)
   {
      status = mp4_next_au_header(p_ctx, extra, is_new_packet);
      if (status != VC_CONTAINER_SUCCESS)
         return status;
   }

   if (p_packet)
   {
      /* Adjust the packet time stamps using deltas */
      p_packet->pts += au_info->cts_delta;
      p_packet->dts += au_info->dts_delta;
   }

   size = au_info->available;
   bytes_left_in_payload = BITS_BYTES_AVAILABLE(p_ctx, payload);
   if (size > bytes_left_in_payload)
   {
      /* AU is fragmented across RTP packets */
      size = bytes_left_in_payload;
   }

   if (p_packet && !(flags & VC_CONTAINER_READ_FLAG_SKIP))
   {
      if (!(flags & VC_CONTAINER_READ_FLAG_INFO))
      {
         if (size > p_packet->buffer_size)
            size = p_packet->buffer_size;

         BITS_COPY_BYTES(p_ctx, payload, size, p_packet->data, "Packet data");
      }
      p_packet->size = size;
   } else {
      BITS_SKIP_BYTES(p_ctx, payload, size, "Packet data");
   }

   if (!(flags & VC_CONTAINER_READ_FLAG_INFO))
      au_info->available -= size;

   return BITS_VALID(p_ctx, payload) ? VC_CONTAINER_SUCCESS : VC_CONTAINER_ERROR_FORMAT_INVALID;
}