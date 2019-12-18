#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {int bits; int* buffer; int /*<<< orphan*/  bytes; } ;
typedef  TYPE_1__ VC_CONTAINER_BITS_T ;

/* Variables and functions */
 int /*<<< orphan*/  vc_container_assert (int) ; 
 int vc_container_bits_available (TYPE_1__*) ; 
 int vc_container_bits_invalidate (TYPE_1__*) ; 

uint32_t vc_container_bits_read_u32(VC_CONTAINER_BITS_T *bit_stream,
      uint32_t value_bits)
{
   uint32_t value = 0;
   uint32_t needed = value_bits;
   uint32_t bits;

   vc_container_assert(value_bits <= 32);

   if (needed > vc_container_bits_available(bit_stream))
      return vc_container_bits_invalidate(bit_stream);

   bits = bit_stream->bits;
   while (needed)
   {
      uint32_t take;

      if (!bits)
      {
         bit_stream->bytes--;
         bit_stream->buffer++;
         bits = 8;
      }

      take = bits;
      if (needed < take) take = needed;

      bits -= take;
      needed -= take;

      value <<= take;
      if (take == 8)
         value |= *bit_stream->buffer;  /* optimize whole byte case */
      else
         value |= (*bit_stream->buffer >> bits) & ((1 << take) - 1);
   }

   bit_stream->bits = bits;
   return value;
}