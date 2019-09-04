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
typedef  int /*<<< orphan*/  CRangeEnc ;
typedef  int /*<<< orphan*/  CLzmaProb ;

/* Variables and functions */
 int /*<<< orphan*/  RangeEnc_EncodeBit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void RcTree_ReverseEncode(CRangeEnc *rc, CLzmaProb *probs, int numBitLevels, UInt32 symbol)
{
  UInt32 m = 1;
  int i;
  for (i = 0; i < numBitLevels; i++)
  {
    UInt32 bit = symbol & 1;
    RangeEnc_EncodeBit(rc, probs + m, bit);
    m = (m << 1) | bit;
    symbol >>= 1;
  }
}