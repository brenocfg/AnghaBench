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
typedef  size_t uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/ * isRepG2; int /*<<< orphan*/ * isRepG1; int /*<<< orphan*/ * isRepG0; int /*<<< orphan*/ ** isRep0Long; } ;
typedef  TYPE_1__ CLzmaEnc ;

/* Variables and functions */
 size_t GET_PRICE (int /*<<< orphan*/ ,size_t) ; 
 size_t GET_PRICE_0 (int /*<<< orphan*/ ) ; 
 size_t GET_PRICE_1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t GetPureRepPrice(CLzmaEnc *p, uint32_t repIndex, uint32_t state, uint32_t posState)
{
  uint32_t price;
  if (repIndex == 0)
  {
    price = GET_PRICE_0(p->isRepG0[state]);
    price += GET_PRICE_1(p->isRep0Long[state][posState]);
  }
  else
  {
    price = GET_PRICE_1(p->isRepG0[state]);
    if (repIndex == 1)
      price += GET_PRICE_0(p->isRepG1[state]);
    else
    {
      price += GET_PRICE_1(p->isRepG1[state]);
      price += GET_PRICE(p->isRepG2[state], repIndex - 2);
    }
  }
  return price;
}