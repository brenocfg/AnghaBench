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
typedef  int UInt32 ;
struct TYPE_3__ {int posEncoders; int** posSlotPrices; int distTableSize; int** distancesPrices; scalar_t__ matchPriceCount; int /*<<< orphan*/  ProbPrices; int /*<<< orphan*/ ** posSlotEncoder; } ;
typedef  int /*<<< orphan*/  CLzmaProb ;
typedef  TYPE_1__ CLzmaEnc ;

/* Variables and functions */
 size_t GetPosSlot1 (int) ; 
 int RcTree_GetPrice (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int RcTree_ReverseGetPrice (int,int,int,int /*<<< orphan*/ ) ; 
 int kEndPosModelIndex ; 
 int kNumAlignBits ; 
 int kNumBitPriceShiftBits ; 
 int kNumFullDistances ; 
 int kNumLenToPosStates ; 
 int /*<<< orphan*/  kNumPosSlotBits ; 
 int kStartPosModelIndex ; 

__attribute__((used)) static void FillDistancesPrices(CLzmaEnc *p)
{
  UInt32 tempPrices[kNumFullDistances];
  UInt32 i, lenToPosState;
  for (i = kStartPosModelIndex; i < kNumFullDistances; i++)
  {
    UInt32 posSlot = GetPosSlot1(i);
    UInt32 footerBits = ((posSlot >> 1) - 1);
    UInt32 base = ((2 | (posSlot & 1)) << footerBits);
    tempPrices[i] = RcTree_ReverseGetPrice(p->posEncoders + base - posSlot - 1, footerBits, i - base, p->ProbPrices);
  }

  for (lenToPosState = 0; lenToPosState < kNumLenToPosStates; lenToPosState++)
  {
    UInt32 posSlot;
    const CLzmaProb *encoder = p->posSlotEncoder[lenToPosState];
    UInt32 *posSlotPrices = p->posSlotPrices[lenToPosState];
    for (posSlot = 0; posSlot < p->distTableSize; posSlot++)
      posSlotPrices[posSlot] = RcTree_GetPrice(encoder, kNumPosSlotBits, posSlot, p->ProbPrices);
    for (posSlot = kEndPosModelIndex; posSlot < p->distTableSize; posSlot++)
      posSlotPrices[posSlot] += ((((posSlot >> 1) - 1) - kNumAlignBits) << kNumBitPriceShiftBits);

    {
      UInt32 *distancesPrices = p->distancesPrices[lenToPosState];
      UInt32 i;
      for (i = 0; i < kStartPosModelIndex; i++)
        distancesPrices[i] = posSlotPrices[i];
      for (; i < kNumFullDistances; i++)
        distancesPrices[i] = posSlotPrices[GetPosSlot1(i)] + tempPrices[i];
    }
  }
  p->matchPriceCount = 0;
}