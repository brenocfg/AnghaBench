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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_5__ {int bits; int* buffer; int /*<<< orphan*/  bytes; } ;
typedef  TYPE_1__ VC_CONTAINER_BITS_T ;

/* Variables and functions */
 int vc_container_bits_available (TYPE_1__*) ; 
 int vc_container_bits_invalidate (TYPE_1__*) ; 

__attribute__((used)) static uint32_t vc_container_bits_get_leading_zero_bits( VC_CONTAINER_BITS_T *bit_stream )
{
   uint32_t leading_zero_bits;
   uint32_t bits_left = vc_container_bits_available(bit_stream);
   uint32_t bits;
   uint8_t mask, current_byte;

   if (!bits_left)
      return vc_container_bits_invalidate(bit_stream);

   /* Cache 'bits' field to avoid repeated pointer access */
   bits = bit_stream->bits;
   if (bits)
   {
      current_byte = *bit_stream->buffer;
      mask = 1 << (bits - 1);
   } else {
      /* Initialize variables to placate the compiler */
      current_byte = 0;
      mask = 0;
   }

   /* Scan for the first one bit, counting the number of zeroes. This gives the
    * number of further bits after the one that are part of the value. See
    * section 9.1 of ITU-T REC H.264 201003 for more details. */

   for (leading_zero_bits = 0; leading_zero_bits < bits_left; leading_zero_bits++)
   {
      if (!bits)
      {
         if (!bit_stream->bytes)
            return vc_container_bits_invalidate(bit_stream);
         bit_stream->bytes--;
         current_byte = *(++bit_stream->buffer);
         bits = 8;
         mask = 0x80;
      }

      bits--;
      bits_left--;
      if (current_byte & mask)
         break;      /* Found the marker bit */

      mask >>= 1;
   }

   /* Check enough bits are left in the stream for the value. */
   if (leading_zero_bits > bits_left)
      return vc_container_bits_invalidate(bit_stream);

   /* Return cached value of bits to the stream */
   bit_stream->bits = bits;

   return leading_zero_bits;
}