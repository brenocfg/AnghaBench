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
typedef  scalar_t__ UInt32 ;
struct TYPE_4__ {scalar_t__ range; int /*<<< orphan*/  low; } ;
typedef  TYPE_1__ CRangeEnc ;
typedef  scalar_t__ CLzmaProb ;

/* Variables and functions */
 int /*<<< orphan*/  RangeEnc_ShiftLow (TYPE_1__*) ; 
 scalar_t__ kBitModelTotal ; 
 scalar_t__ kNumBitModelTotalBits ; 
 scalar_t__ kNumMoveBits ; 
 scalar_t__ kTopValue ; 

__attribute__((used)) static void RangeEnc_EncodeBit(CRangeEnc *p, CLzmaProb *prob, UInt32 symbol)
{
  UInt32 ttt = *prob;
  UInt32 newBound = (p->range >> kNumBitModelTotalBits) * ttt;
  if (symbol == 0)
  {
    p->range = newBound;
    ttt += (kBitModelTotal - ttt) >> kNumMoveBits;
  }
  else
  {
    p->low += newBound;
    p->range -= newBound;
    ttt -= ttt >> kNumMoveBits;
  }
  *prob = (CLzmaProb)ttt;
  if (p->range < kTopValue)
  {
    p->range <<= 8;
    RangeEnc_ShiftLow(p);
  }
}