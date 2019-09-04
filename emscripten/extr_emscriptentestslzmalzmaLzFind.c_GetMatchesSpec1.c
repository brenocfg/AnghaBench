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
typedef  int UInt32 ;
typedef  int CLzRef ;
typedef  scalar_t__ Byte ;

/* Variables and functions */
 int kEmptyHashValue ; 

UInt32 * GetMatchesSpec1(UInt32 lenLimit, UInt32 curMatch, UInt32 pos, const Byte *cur, CLzRef *son,
    UInt32 _cyclicBufferPos, UInt32 _cyclicBufferSize, UInt32 cutValue,
    UInt32 *distances, UInt32 maxLen)
{
  CLzRef *ptr0 = son + (_cyclicBufferPos << 1) + 1;
  CLzRef *ptr1 = son + (_cyclicBufferPos << 1);
  UInt32 len0 = 0, len1 = 0;
  for (;;)
  {
    UInt32 delta = pos - curMatch;
    if (cutValue-- == 0 || delta >= _cyclicBufferSize)
    {
      *ptr0 = *ptr1 = kEmptyHashValue;
      return distances;
    }
    {
      CLzRef *pair = son + ((_cyclicBufferPos - delta + ((delta > _cyclicBufferPos) ? _cyclicBufferSize : 0)) << 1);
      const Byte *pb = cur - delta;
      UInt32 len = (len0 < len1 ? len0 : len1);
      if (pb[len] == cur[len])
      {
        if (++len != lenLimit && pb[len] == cur[len])
          while (++len != lenLimit)
            if (pb[len] != cur[len])
              break;
        if (maxLen < len)
        {
          *distances++ = maxLen = len;
          *distances++ = delta - 1;
          if (len == lenLimit)
          {
            *ptr1 = pair[0];
            *ptr0 = pair[1];
            return distances;
          }
        }
      }
      if (pb[len] < cur[len])
      {
        *ptr1 = curMatch;
        ptr1 = pair + 1;
        curMatch = *ptr1;
        len1 = len;
      }
      else
      {
        *ptr0 = curMatch;
        ptr0 = pair;
        curMatch = *ptr0;
        len0 = len;
      }
    }
  }
}