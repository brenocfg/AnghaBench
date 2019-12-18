#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_3__ {int* fast; int* values; int* size; } ;
typedef  TYPE_1__ rjpeg_huffman ;
typedef  scalar_t__ int16_t ;

/* Variables and functions */
 int FAST_BITS ; 

__attribute__((used)) static void rjpeg_build_fast_ac(int16_t *fast_ac, rjpeg_huffman *h)
{
   int i;

   for (i = 0; i < (1 << FAST_BITS); ++i)
   {
      uint8_t fast = h->fast[i];

      fast_ac[i] = 0;

      if (fast < 255)
      {
         int rs      = h->values[fast];
         int run     = (rs >> 4) & 15;
         int magbits = rs & 15;
         int len     = h->size[fast];

         if (magbits && len + magbits <= FAST_BITS)
         {
            /* magnitude code followed by receive_extend code */
            int k = ((i << len) & ((1 << FAST_BITS) - 1)) >> (FAST_BITS - magbits);
            int m = 1 << (magbits - 1);
            if (k < m)
               k += (-1 << magbits) + 1;

            /* if the result is small enough, we can fit it in fast_ac table */
            if (k >= -128 && k <= 127)
               fast_ac[i] = (int16_t) ((k << 8) + (run << 4) + (len + magbits));
         }
      }
   }
}