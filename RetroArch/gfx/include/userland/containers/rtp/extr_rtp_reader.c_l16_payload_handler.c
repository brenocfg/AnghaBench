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
typedef  int /*<<< orphan*/  VC_CONTAINER_TRACK_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_4__ {int size; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ VC_CONTAINER_PACKET_T ;

/* Variables and functions */
 int VC_CONTAINER_READ_FLAG_INFO ; 
 int VC_CONTAINER_READ_FLAG_SKIP ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 scalar_t__ generic_payload_handler (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T l16_payload_handler(VC_CONTAINER_T *p_ctx,
      VC_CONTAINER_TRACK_T *track,
      VC_CONTAINER_PACKET_T *p_packet,
      uint32_t flags)
{
   VC_CONTAINER_STATUS_T status;

   /* Most aspects are handled adequately by the generic handler */
   status = generic_payload_handler(p_ctx, track, p_packet, flags);
   if (status != VC_CONTAINER_SUCCESS)
      return status;

   if (p_packet && !(flags & (VC_CONTAINER_READ_FLAG_SKIP | VC_CONTAINER_READ_FLAG_INFO)))
   {
      uint8_t *ptr, *end_ptr;

      /* Ensure packet size is even */
      p_packet->size &= ~1;

      /* Swap bytes of each sample, to get host order instead of network order */
      for (ptr = p_packet->data, end_ptr = ptr + p_packet->size; ptr < end_ptr; ptr += 2)
      {
         uint8_t high_byte = ptr[0];
         ptr[0] = ptr[1];
         ptr[1] = high_byte;
      }
   }

   return status;
}