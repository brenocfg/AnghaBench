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

/* Variables and functions */
 int kBitModelTotal ; 
 int const kNumBitModelTotalBits ; 
 int kNumBitPriceShiftBits ; 
 int kNumMoveReducingBits ; 

void LzmaEnc_InitPriceTables(UInt32 *ProbPrices)
{
  UInt32 i;
  for (i = (1 << kNumMoveReducingBits) / 2; i < kBitModelTotal; i += (1 << kNumMoveReducingBits))
  {
    const int kCyclesBits = kNumBitPriceShiftBits;
    UInt32 w = i;
    UInt32 bitCount = 0;
    int j;
    for (j = 0; j < kCyclesBits; j++)
    {
      w = w * w;
      bitCount <<= 1;
      while (w >= ((UInt32)1 << 16))
      {
        w >>= 1;
        bitCount++;
      }
    }
    ProbPrices[i >> kNumMoveReducingBits] = ((kNumBitModelTotalBits << kCyclesBits) - 15 - bitCount);
  }
}