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
typedef  int uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 scalar_t__ Test86MSuint8_t (int) ; 
 int /*<<< orphan*/ * kMaskToAllowedStatus ; 
 int* kMaskToBitNumber ; 

size_t x86_Convert(uint8_t *data, size_t size, uint32_t ip, uint32_t *state, int encoding)
{
   size_t bufferPos = 0, prevPosT;
   uint32_t prevMask = *state & 0x7;
   if (size < 5)
      return 0;
   ip += 5;
   prevPosT = (size_t)0 - 1;

   for (;;)
   {
      uint8_t *p = data + bufferPos;
      uint8_t *limit = data + size - 4;
      for (; p < limit; p++)
         if ((*p & 0xFE) == 0xE8)
            break;
      bufferPos = (size_t)(p - data);
      if (p >= limit)
         break;
      prevPosT = bufferPos - prevPosT;
      if (prevPosT > 3)
         prevMask = 0;
      else
      {
         prevMask = (prevMask << ((int)prevPosT - 1)) & 0x7;
         if (prevMask != 0)
         {
            uint8_t b = p[4 - kMaskToBitNumber[prevMask]];
            if (!kMaskToAllowedStatus[prevMask] || Test86MSuint8_t(b))
            {
               prevPosT = bufferPos;
               prevMask = ((prevMask << 1) & 0x7) | 1;
               bufferPos++;
               continue;
            }
         }
      }
      prevPosT = bufferPos;

      if (Test86MSuint8_t(p[4]))
      {
         uint32_t src = ((uint32_t)p[4] << 24) | ((uint32_t)p[3] << 16) | ((uint32_t)p[2] << 8) | ((uint32_t)p[1]);
         uint32_t dest;
         for (;;)
         {
            uint8_t b;
            int idx;
            if (encoding)
               dest = (ip + (uint32_t)bufferPos) + src;
            else
               dest = src - (ip + (uint32_t)bufferPos);
            if (prevMask == 0)
               break;
            idx = kMaskToBitNumber[prevMask] * 8;
            b = (uint8_t)(dest >> (24 - idx));
            if (!Test86MSuint8_t(b))
               break;
            src = dest ^ ((1 << (32 - idx)) - 1);
         }
         p[4] = (uint8_t)(~(((dest >> 24) & 1) - 1));
         p[3] = (uint8_t)(dest >> 16);
         p[2] = (uint8_t)(dest >> 8);
         p[1] = (uint8_t)dest;
         bufferPos += 5;
      }
      else
      {
         prevMask = ((prevMask << 1) & 0x7) | 1;
         bufferPos++;
      }
   }
   prevPosT = bufferPos - prevPosT;
   *state = ((prevPosT > 3) ? 0 : ((prevMask << ((int)prevPosT - 1)) & 0x7));
   return bufferPos;
}