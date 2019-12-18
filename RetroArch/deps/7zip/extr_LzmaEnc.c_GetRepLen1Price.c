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
struct TYPE_3__ {int /*<<< orphan*/ ** isRep0Long; int /*<<< orphan*/ * isRepG0; } ;
typedef  TYPE_1__ CLzmaEnc ;

/* Variables and functions */
 size_t GET_PRICE_0 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t GetRepLen1Price(CLzmaEnc *p, uint32_t state, uint32_t posState)
{
  return
    GET_PRICE_0(p->isRepG0[state]) +
    GET_PRICE_0(p->isRep0Long[state][posState]);
}