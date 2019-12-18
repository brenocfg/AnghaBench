#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint64_t ;
struct TYPE_15__ {size_t dicBufSize; size_t dicPos; int /*<<< orphan*/ * dic; } ;
struct TYPE_12__ {scalar_t__ size; int /*<<< orphan*/  data; } ;
struct TYPE_14__ {TYPE_1__ Props; } ;
struct TYPE_13__ {scalar_t__ (* Skip ) (void*,size_t) ;scalar_t__ (* Look ) (void*,void const**,size_t*) ;} ;
typedef  scalar_t__ SRes ;
typedef  int /*<<< orphan*/  ISzAlloc ;
typedef  TYPE_2__ ILookInStream ;
typedef  scalar_t__ ELzmaStatus ;
typedef  TYPE_3__ CSzCoderInfo ;
typedef  TYPE_4__ CLzmaDec ;

/* Variables and functions */
 int /*<<< orphan*/  LZMA_FINISH_END ; 
 scalar_t__ LZMA_STATUS_FINISHED_WITH_MARK ; 
 scalar_t__ LZMA_STATUS_MAYBE_FINISHED_WITHOUT_MARK ; 
 int /*<<< orphan*/  LzmaDec_AllocateProbs (TYPE_4__*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LzmaDec_Construct (TYPE_4__*) ; 
 scalar_t__ LzmaDec_DecodeToDic (TYPE_4__*,size_t,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  LzmaDec_FreeProbs (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LzmaDec_Init (TYPE_4__*) ; 
 int /*<<< orphan*/  RINOK (int /*<<< orphan*/ ) ; 
 scalar_t__ SZ_ERROR_DATA ; 
 scalar_t__ SZ_OK ; 
 scalar_t__ stub1 (void*,void const**,size_t*) ; 
 scalar_t__ stub2 (void*,size_t) ; 

__attribute__((used)) static SRes SzDecodeLzma(CSzCoderInfo *coder, uint64_t inSize, ILookInStream *inStream,
    uint8_t *outBuffer, size_t outSize, ISzAlloc *allocMain)
{
  CLzmaDec state;
  SRes res = SZ_OK;

  LzmaDec_Construct(&state);
  RINOK(LzmaDec_AllocateProbs(&state, coder->Props.data, (unsigned)coder->Props.size, allocMain));
  state.dic = outBuffer;
  state.dicBufSize = outSize;
  LzmaDec_Init(&state);

  for (;;)
  {
    uint8_t *inBuf = NULL;
    size_t lookahead = (1 << 18);
    if (lookahead > inSize)
      lookahead = (size_t)inSize;
    res = inStream->Look((void *)inStream, (const void **)&inBuf, &lookahead);
    if (res != SZ_OK)
      break;

    {
      size_t inProcessed = (size_t)lookahead, dicPos = state.dicPos;
      ELzmaStatus status;
      res = LzmaDec_DecodeToDic(&state, outSize, inBuf, &inProcessed, LZMA_FINISH_END, &status);
      lookahead -= inProcessed;
      inSize -= inProcessed;
      if (res != SZ_OK)
        break;
      if (state.dicPos == state.dicBufSize || (inProcessed == 0 && dicPos == state.dicPos))
      {
        if (state.dicBufSize != outSize || lookahead != 0 ||
            (status != LZMA_STATUS_FINISHED_WITH_MARK &&
             status != LZMA_STATUS_MAYBE_FINISHED_WITHOUT_MARK))
          res = SZ_ERROR_DATA;
        break;
      }
      res = inStream->Skip((void *)inStream, inProcessed);
      if (res != SZ_OK)
        break;
    }
  }

  LzmaDec_FreeProbs(&state, allocMain);
  return res;
}