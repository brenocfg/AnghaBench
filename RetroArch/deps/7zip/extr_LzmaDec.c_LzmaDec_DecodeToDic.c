#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_8__ {scalar_t__ remainLen; scalar_t__ needFlush; scalar_t__ tempBufSize; scalar_t__* tempBuf; size_t dicPos; scalar_t__ code; scalar_t__ const* buf; scalar_t__ needInitState; } ;
typedef  int /*<<< orphan*/  SRes ;
typedef  int /*<<< orphan*/  ELzmaStatus ;
typedef  scalar_t__ ELzmaFinishMode ;
typedef  TYPE_1__ CLzmaDec ;

/* Variables and functions */
 int DUMMY_ERROR ; 
 int DUMMY_MATCH ; 
 scalar_t__ LZMA_FINISH_ANY ; 
 size_t LZMA_REQUIRED_INPUT_MAX ; 
 int /*<<< orphan*/  LZMA_STATUS_FINISHED_WITH_MARK ; 
 int /*<<< orphan*/  LZMA_STATUS_MAYBE_FINISHED_WITHOUT_MARK ; 
 int /*<<< orphan*/  LZMA_STATUS_NEEDS_MORE_INPUT ; 
 int /*<<< orphan*/  LZMA_STATUS_NOT_FINISHED ; 
 int /*<<< orphan*/  LZMA_STATUS_NOT_SPECIFIED ; 
 scalar_t__ LzmaDec_DecodeReal2 (TYPE_1__*,size_t,scalar_t__ const*) ; 
 int /*<<< orphan*/  LzmaDec_InitRc (TYPE_1__*,scalar_t__*) ; 
 int /*<<< orphan*/  LzmaDec_InitStateReal (TYPE_1__*) ; 
 int LzmaDec_TryDummy (TYPE_1__*,scalar_t__ const*,unsigned int) ; 
 int /*<<< orphan*/  LzmaDec_WriteRem (TYPE_1__*,size_t) ; 
 scalar_t__ RC_INIT_SIZE ; 
 int /*<<< orphan*/  SZ_ERROR_DATA ; 
 int /*<<< orphan*/  SZ_OK ; 
 scalar_t__ kMatchSpecLenStart ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__ const*,size_t) ; 

SRes LzmaDec_DecodeToDic(CLzmaDec *p, size_t dicLimit, const uint8_t *src, size_t *srcLen,
      ELzmaFinishMode finishMode, ELzmaStatus *status)
{
   size_t inSize = *srcLen;
   (*srcLen) = 0;
   LzmaDec_WriteRem(p, dicLimit);

   *status = LZMA_STATUS_NOT_SPECIFIED;

   while (p->remainLen != kMatchSpecLenStart)
   {
      int checkEndMarkNow;

      if (p->needFlush != 0)
      {
         for (; inSize > 0 && p->tempBufSize < RC_INIT_SIZE; (*srcLen)++, inSize--)
            p->tempBuf[p->tempBufSize++] = *src++;
         if (p->tempBufSize < RC_INIT_SIZE)
         {
            *status = LZMA_STATUS_NEEDS_MORE_INPUT;
            return SZ_OK;
         }
         if (p->tempBuf[0] != 0)
            return SZ_ERROR_DATA;

         LzmaDec_InitRc(p, p->tempBuf);
         p->tempBufSize = 0;
      }

      checkEndMarkNow = 0;
      if (p->dicPos >= dicLimit)
      {
         if (p->remainLen == 0 && p->code == 0)
         {
            *status = LZMA_STATUS_MAYBE_FINISHED_WITHOUT_MARK;
            return SZ_OK;
         }
         if (finishMode == LZMA_FINISH_ANY)
         {
            *status = LZMA_STATUS_NOT_FINISHED;
            return SZ_OK;
         }
         if (p->remainLen != 0)
         {
            *status = LZMA_STATUS_NOT_FINISHED;
            return SZ_ERROR_DATA;
         }
         checkEndMarkNow = 1;
      }

      if (p->needInitState)
         LzmaDec_InitStateReal(p);

      if (p->tempBufSize == 0)
      {
         size_t processed;
         const uint8_t *bufLimit;
         if (inSize < LZMA_REQUIRED_INPUT_MAX || checkEndMarkNow)
         {
            int dummyRes = LzmaDec_TryDummy(p, src, inSize);
            if (dummyRes == DUMMY_ERROR)
            {
               memcpy(p->tempBuf, src, inSize);
               p->tempBufSize = (unsigned)inSize;
               (*srcLen) += inSize;
               *status = LZMA_STATUS_NEEDS_MORE_INPUT;
               return SZ_OK;
            }
            if (checkEndMarkNow && dummyRes != DUMMY_MATCH)
            {
               *status = LZMA_STATUS_NOT_FINISHED;
               return SZ_ERROR_DATA;
            }
            bufLimit = src;
         }
         else
            bufLimit = src + inSize - LZMA_REQUIRED_INPUT_MAX;
         p->buf = src;
         if (LzmaDec_DecodeReal2(p, dicLimit, bufLimit) != 0)
            return SZ_ERROR_DATA;
         processed = (size_t)(p->buf - src);
         (*srcLen) += processed;
         src += processed;
         inSize -= processed;
      }
      else
      {
         unsigned rem = p->tempBufSize, lookAhead = 0;
         while (rem < LZMA_REQUIRED_INPUT_MAX && lookAhead < inSize)
            p->tempBuf[rem++] = src[lookAhead++];
         p->tempBufSize = rem;
         if (rem < LZMA_REQUIRED_INPUT_MAX || checkEndMarkNow)
         {
            int dummyRes = LzmaDec_TryDummy(p, p->tempBuf, rem);
            if (dummyRes == DUMMY_ERROR)
            {
               (*srcLen) += lookAhead;
               *status = LZMA_STATUS_NEEDS_MORE_INPUT;
               return SZ_OK;
            }
            if (checkEndMarkNow && dummyRes != DUMMY_MATCH)
            {
               *status = LZMA_STATUS_NOT_FINISHED;
               return SZ_ERROR_DATA;
            }
         }
         p->buf = p->tempBuf;
         if (LzmaDec_DecodeReal2(p, dicLimit, p->buf) != 0)
            return SZ_ERROR_DATA;
         lookAhead -= (rem - (unsigned)(p->buf - p->tempBuf));
         (*srcLen) += lookAhead;
         src += lookAhead;
         inSize -= lookAhead;
         p->tempBufSize = 0;
      }
   }
   if (p->code == 0)
      *status = LZMA_STATUS_FINISHED_WITH_MARK;
   return (p->code == 0) ? SZ_OK : SZ_ERROR_DATA;
}