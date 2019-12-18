#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  size_t uint32_t ;
typedef  size_t uint16_t ;

/* Variables and functions */

__attribute__((used)) static void state_manager_raw_decompress(const void *patch,
      size_t patchlen, void *data, size_t datalen)
{
   uint16_t         *out16 = (uint16_t*)data;
   const uint16_t *patch16 = (const uint16_t*)patch;

   (void)patchlen;
   (void)datalen;

   for (;;)
   {
      uint16_t numchanged = *(patch16++);

      if (numchanged)
      {
         uint16_t i;

         out16 += *patch16++;

         /* We could do memcpy, but it seems that memcpy has a
          * constant-per-call overhead that actually shows up.
          *
          * Our average size in here seems to be 8 or something.
          * Therefore, we do something with lower overhead. */
         for (i = 0; i < numchanged; i++)
            out16[i] = patch16[i];

         patch16 += numchanged;
         out16 += numchanged;
      }
      else
      {
         uint32_t numunchanged = patch16[0] | (patch16[1] << 16);

         if (!numunchanged)
            break;
         patch16 += 2;
         out16 += numunchanged;
      }
   }
}