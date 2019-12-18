#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_10__ {size_t dicPos; } ;
struct TYPE_9__ {scalar_t__ state; size_t unpackSize; scalar_t__ control; int needInitProp; int needInitState; int needInitDic; size_t packSize; TYPE_2__ decoder; } ;
typedef  int /*<<< orphan*/  SRes ;
typedef  scalar_t__ ELzmaStatus ;
typedef  scalar_t__ ELzmaFinishMode ;
typedef  TYPE_1__ CLzma2Dec ;

/* Variables and functions */
 scalar_t__ LZMA2_CONTROL_COPY_RESET_DIC ; 
 int LZMA2_GET_LZMA_MODE (TYPE_1__*) ; 
 scalar_t__ LZMA2_IS_UNCOMPRESSED_STATE (TYPE_1__*) ; 
 scalar_t__ LZMA2_STATE_CONTROL ; 
 scalar_t__ LZMA2_STATE_DATA ; 
 scalar_t__ LZMA2_STATE_DATA_CONT ; 
 scalar_t__ LZMA2_STATE_ERROR ; 
 scalar_t__ LZMA2_STATE_FINISHED ; 
 scalar_t__ LZMA_FINISH_ANY ; 
 scalar_t__ LZMA_FINISH_END ; 
 scalar_t__ LZMA_STATUS_FINISHED_WITH_MARK ; 
 scalar_t__ LZMA_STATUS_MAYBE_FINISHED_WITHOUT_MARK ; 
 scalar_t__ LZMA_STATUS_NEEDS_MORE_INPUT ; 
 scalar_t__ LZMA_STATUS_NOT_FINISHED ; 
 scalar_t__ LZMA_STATUS_NOT_SPECIFIED ; 
 scalar_t__ Lzma2Dec_UpdateState (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LzmaDec_DecodeToDic (TYPE_2__*,size_t,int /*<<< orphan*/  const*,size_t*,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  LzmaDec_InitDicAndState (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  LzmaDec_UpdateWithUncompressed (TYPE_2__*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  RINOK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SZ_ERROR_DATA ; 
 int /*<<< orphan*/  SZ_OK ; 

SRes Lzma2Dec_DecodeToDic(CLzma2Dec *p, size_t dicLimit,
      const uint8_t *src, size_t *srcLen, ELzmaFinishMode finishMode, ELzmaStatus *status)
{
   size_t inSize = *srcLen;
   *srcLen = 0;
   *status = LZMA_STATUS_NOT_SPECIFIED;

   while (p->state != LZMA2_STATE_FINISHED)
   {
      size_t dicPos = p->decoder.dicPos;
      if (p->state == LZMA2_STATE_ERROR)
         return SZ_ERROR_DATA;
      if (dicPos == dicLimit && finishMode == LZMA_FINISH_ANY)
      {
         *status = LZMA_STATUS_NOT_FINISHED;
         return SZ_OK;
      }
      if (p->state != LZMA2_STATE_DATA && p->state != LZMA2_STATE_DATA_CONT)
      {
         if (*srcLen == inSize)
         {
            *status = LZMA_STATUS_NEEDS_MORE_INPUT;
            return SZ_OK;
         }
         (*srcLen)++;
         p->state = Lzma2Dec_UpdateState(p, *src++);
         continue;
      }
      {
         size_t destSizeCur = dicLimit - dicPos;
         size_t srcSizeCur = inSize - *srcLen;
         ELzmaFinishMode curFinishMode = LZMA_FINISH_ANY;

         if (p->unpackSize <= destSizeCur)
         {
            destSizeCur = (size_t)p->unpackSize;
            curFinishMode = LZMA_FINISH_END;
         }

         if (LZMA2_IS_UNCOMPRESSED_STATE(p))
         {
            if (*srcLen == inSize)
            {
               *status = LZMA_STATUS_NEEDS_MORE_INPUT;
               return SZ_OK;
            }

            if (p->state == LZMA2_STATE_DATA)
            {
               bool initDic = (p->control == LZMA2_CONTROL_COPY_RESET_DIC);
               if (initDic)
                  p->needInitProp = p->needInitState = true;
               else if (p->needInitDic)
                  return SZ_ERROR_DATA;
               p->needInitDic = false;
               LzmaDec_InitDicAndState(&p->decoder, initDic, false);
            }

            if (srcSizeCur > destSizeCur)
               srcSizeCur = destSizeCur;

            if (srcSizeCur == 0)
               return SZ_ERROR_DATA;

            LzmaDec_UpdateWithUncompressed(&p->decoder, src, srcSizeCur);

            src += srcSizeCur;
            *srcLen += srcSizeCur;
            p->unpackSize -= (uint32_t)srcSizeCur;
            p->state = (p->unpackSize == 0) ? LZMA2_STATE_CONTROL : LZMA2_STATE_DATA_CONT;
         }
         else
         {
            size_t outSizeProcessed;
            SRes res;

            if (p->state == LZMA2_STATE_DATA)
            {
               int mode = LZMA2_GET_LZMA_MODE(p);
               bool initDic = (mode == 3);
               bool initState = (mode > 0);
               if ((!initDic && p->needInitDic) || (!initState && p->needInitState))
                  return SZ_ERROR_DATA;

               LzmaDec_InitDicAndState(&p->decoder, initDic, initState);
               p->needInitDic = false;
               p->needInitState = false;
               p->state = LZMA2_STATE_DATA_CONT;
            }
            if (srcSizeCur > p->packSize)
               srcSizeCur = (size_t)p->packSize;

            res = LzmaDec_DecodeToDic(&p->decoder, dicPos + destSizeCur, src, &srcSizeCur, curFinishMode, status);

            src += srcSizeCur;
            *srcLen += srcSizeCur;
            p->packSize -= (uint32_t)srcSizeCur;

            outSizeProcessed = p->decoder.dicPos - dicPos;
            p->unpackSize -= (uint32_t)outSizeProcessed;

            RINOK(res);
            if (*status == LZMA_STATUS_NEEDS_MORE_INPUT)
               return res;

            if (srcSizeCur == 0 && outSizeProcessed == 0)
            {
               if (*status != LZMA_STATUS_MAYBE_FINISHED_WITHOUT_MARK ||
                     p->unpackSize != 0 || p->packSize != 0)
                  return SZ_ERROR_DATA;
               p->state = LZMA2_STATE_CONTROL;
            }
            if (*status == LZMA_STATUS_MAYBE_FINISHED_WITHOUT_MARK)
               *status = LZMA_STATUS_NOT_FINISHED;
         }
      }
   }
   *status = LZMA_STATUS_FINISHED_WITH_MARK;
   return SZ_OK;
}