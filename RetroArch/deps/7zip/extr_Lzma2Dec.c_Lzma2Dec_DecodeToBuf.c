#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {size_t dicPos; size_t dicBufSize; scalar_t__ dic; } ;
struct TYPE_6__ {TYPE_1__ decoder; } ;
typedef  scalar_t__ SRes ;
typedef  int /*<<< orphan*/  ELzmaStatus ;
typedef  int /*<<< orphan*/  ELzmaFinishMode ;
typedef  TYPE_2__ CLzma2Dec ;

/* Variables and functions */
 int /*<<< orphan*/  LZMA_FINISH_ANY ; 
 scalar_t__ Lzma2Dec_DecodeToDic (TYPE_2__*,size_t,int /*<<< orphan*/  const*,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ SZ_OK ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,size_t) ; 

SRes Lzma2Dec_DecodeToBuf(CLzma2Dec *p, uint8_t *dest, size_t *destLen, const uint8_t *src, size_t *srcLen, ELzmaFinishMode finishMode, ELzmaStatus *status)
{
   size_t outSize = *destLen, inSize = *srcLen;
   *srcLen = *destLen = 0;
   for (;;)
   {
      size_t srcSizeCur = inSize, outSizeCur, dicPos;
      ELzmaFinishMode curFinishMode;
      SRes res;
      if (p->decoder.dicPos == p->decoder.dicBufSize)
         p->decoder.dicPos = 0;
      dicPos = p->decoder.dicPos;
      if (outSize > p->decoder.dicBufSize - dicPos)
      {
         outSizeCur = p->decoder.dicBufSize;
         curFinishMode = LZMA_FINISH_ANY;
      }
      else
      {
         outSizeCur = dicPos + outSize;
         curFinishMode = finishMode;
      }

      res = Lzma2Dec_DecodeToDic(p, outSizeCur, src, &srcSizeCur, curFinishMode, status);
      src += srcSizeCur;
      inSize -= srcSizeCur;
      *srcLen += srcSizeCur;
      outSizeCur = p->decoder.dicPos - dicPos;
      memcpy(dest, p->decoder.dic + dicPos, outSizeCur);
      dest += outSizeCur;
      outSize -= outSizeCur;
      *destLen += outSizeCur;
      if (res != 0)
         return res;
      if (outSizeCur == 0 || outSize == 0)
         return SZ_OK;
   }
}