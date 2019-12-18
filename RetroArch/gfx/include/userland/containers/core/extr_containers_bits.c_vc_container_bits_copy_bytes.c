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
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {scalar_t__ bytes; scalar_t__ buffer; int /*<<< orphan*/  bits; } ;
typedef  TYPE_1__ VC_CONTAINER_BITS_T ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  vc_container_assert (int) ; 
 int /*<<< orphan*/  vc_container_bits_invalidate (TYPE_1__*) ; 

void vc_container_bits_copy_bytes(VC_CONTAINER_BITS_T *bit_stream,
      uint32_t bytes_to_copy,
      uint8_t *dst)
{
   vc_container_assert(!bit_stream->bits);

   if (bit_stream->bytes < bytes_to_copy)
   {
      /* Not enough data */
      vc_container_bits_invalidate(bit_stream);
      return;
   }

   /* When the number of bits is zero, the next byte to take is at buffer + 1 */
   memcpy(dst, bit_stream->buffer + 1, bytes_to_copy);
   bit_stream->buffer += bytes_to_copy;
   bit_stream->bytes -= bytes_to_copy;
}