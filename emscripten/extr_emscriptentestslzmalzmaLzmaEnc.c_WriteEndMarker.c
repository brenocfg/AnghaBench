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
typedef  size_t UInt32 ;
struct TYPE_3__ {size_t state; int /*<<< orphan*/  posAlignEncoder; int /*<<< orphan*/  rc; int /*<<< orphan*/ * posSlotEncoder; int /*<<< orphan*/  ProbPrices; int /*<<< orphan*/  fastMode; int /*<<< orphan*/  lenEnc; int /*<<< orphan*/ * isRep; int /*<<< orphan*/ ** isMatch; } ;
typedef  TYPE_1__ CLzmaEnc ;

/* Variables and functions */
 size_t GetLenToPosState (size_t) ; 
 size_t LZMA_MATCH_LEN_MIN ; 
 int /*<<< orphan*/  LenEnc_Encode2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RangeEnc_EncodeBit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RangeEnc_EncodeDirectBits (int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  RcTree_Encode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  RcTree_ReverseEncode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kAlignMask ; 
 size_t* kMatchNextStates ; 
 size_t kNumAlignBits ; 
 int kNumPosSlotBits ; 

__attribute__((used)) static void WriteEndMarker(CLzmaEnc *p, UInt32 posState)
{
  UInt32 len;
  RangeEnc_EncodeBit(&p->rc, &p->isMatch[p->state][posState], 1);
  RangeEnc_EncodeBit(&p->rc, &p->isRep[p->state], 0);
  p->state = kMatchNextStates[p->state];
  len = LZMA_MATCH_LEN_MIN;
  LenEnc_Encode2(&p->lenEnc, &p->rc, len - LZMA_MATCH_LEN_MIN, posState, !p->fastMode, p->ProbPrices);
  RcTree_Encode(&p->rc, p->posSlotEncoder[GetLenToPosState(len)], kNumPosSlotBits, (1 << kNumPosSlotBits) - 1);
  RangeEnc_EncodeDirectBits(&p->rc, (((UInt32)1 << 30) - 1) >> kNumAlignBits, 30 - kNumAlignBits);
  RcTree_ReverseEncode(&p->rc, p->posAlignEncoder, kNumAlignBits, kAlignMask);
}