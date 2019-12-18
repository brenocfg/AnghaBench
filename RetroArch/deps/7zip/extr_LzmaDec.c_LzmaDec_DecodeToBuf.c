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
struct TYPE_4__ {size_t dicPos; size_t dicBufSize; scalar_t__ dic; } ;
typedef  scalar_t__ SRes ;
typedef  int /*<<< orphan*/  ELzmaStatus ;
typedef  int /*<<< orphan*/  ELzmaFinishMode ;
typedef  TYPE_1__ CLzmaDec ;

/* Variables and functions */
 int /*<<< orphan*/  LZMA_FINISH_ANY ; 
 scalar_t__ LzmaDec_DecodeToDic (TYPE_1__*,size_t,int /*<<< orphan*/  const*,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ SZ_OK ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,size_t) ; 

SRes LzmaDec_DecodeToBuf(CLzmaDec *p, uint8_t *dest, size_t *destLen, const uint8_t *src, size_t *srcLen, ELzmaFinishMode finishMode, ELzmaStatus *status)
{
   size_t outSize = *destLen;
   size_t inSize = *srcLen;
   *srcLen = *destLen = 0;
   for (;;)
   {
      size_t inSizeCur = inSize, outSizeCur, dicPos;
      ELzmaFinishMode curFinishMode;
      SRes res;
      if (p->dicPos == p->dicBufSize)
         p->dicPos = 0;
      dicPos = p->dicPos;
      if (outSize > p->dicBufSize - dicPos)
      {
         outSizeCur = p->dicBufSize;
         curFinishMode = LZMA_FINISH_ANY;
      }
      else
      {
         outSizeCur = dicPos + outSize;
         curFinishMode = finishMode;
      }

      res = LzmaDec_DecodeToDic(p, outSizeCur, src, &inSizeCur, curFinishMode, status);
      src += inSizeCur;
      inSize -= inSizeCur;
      *srcLen += inSizeCur;
      outSizeCur = p->dicPos - dicPos;
      memcpy(dest, p->dic + dicPos, outSizeCur);
      dest += outSizeCur;
      outSize -= outSizeCur;
      *destLen += outSizeCur;
      if (res != 0)
         return res;
      if (outSizeCur == 0 || outSize == 0)
         return SZ_OK;
   }
}