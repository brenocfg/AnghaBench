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
typedef  scalar_t__ UInt32 ;
typedef  int /*<<< orphan*/  CLenPriceEnc ;

/* Variables and functions */
 int /*<<< orphan*/  LenPriceEnc_UpdateTable (int /*<<< orphan*/ *,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static void LenPriceEnc_UpdateTables(CLenPriceEnc *p, UInt32 numPosStates, UInt32 *ProbPrices)
{
  UInt32 posState;
  for (posState = 0; posState < numPosStates; posState++)
    LenPriceEnc_UpdateTable(p, posState, ProbPrices);
}