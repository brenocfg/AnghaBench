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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  CLzmaProb ;

/* Variables and functions */
 scalar_t__ GET_PRICEa (int /*<<< orphan*/  const,int) ; 

__attribute__((used)) static uint32_t LitEnc_GetPriceMatched(const CLzmaProb *probs, uint32_t symbol, uint32_t matchByte, const uint32_t *ProbPrices)
{
  uint32_t price = 0;
  uint32_t offs = 0x100;
  symbol |= 0x100;
  do
  {
    matchByte <<= 1;
    price += GET_PRICEa(probs[offs + (matchByte & offs) + (symbol >> 8)], (symbol >> 7) & 1);
    symbol <<= 1;
    offs &= ~(matchByte ^ symbol);
  }
  while (symbol < 0x10000);
  return price;
}