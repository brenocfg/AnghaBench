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
typedef  size_t u8_t ;
struct zsRcCell {size_t currentRateIndex; scalar_t__ operationRateCount; size_t* operationRateSet; } ;

/* Variables and functions */

u8_t zfRateCtrlGetHigherRate(struct zsRcCell* rcCell)
{
    u8_t rateIndex;

    rateIndex = rcCell->currentRateIndex
            + (((rcCell->currentRateIndex+1) < rcCell->operationRateCount)?1:0);
    return rcCell->operationRateSet[rateIndex];
}