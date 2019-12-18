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
typedef  scalar_t__ u8_t ;
typedef  size_t u16_t ;
struct zsRcCell {size_t operationRateCount; scalar_t__* operationRateSet; size_t currentRateIndex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_LV_0 ; 
 int /*<<< orphan*/  zm_msg1_tx (int /*<<< orphan*/ ,char*,scalar_t__) ; 

u8_t zfRateCtrlRateDiff(struct zsRcCell* rcCell, u8_t retryRate)
{
    u16_t i;

    /* Find retryRate in operationRateSet[] */
    for (i=0; i<rcCell->operationRateCount; i++)
    {
        if (retryRate == rcCell->operationRateSet[i])
        {
            if (i < rcCell->currentRateIndex)
            {
                return ((rcCell->currentRateIndex - i)+1)>>1;
            }
            else if (i == rcCell->currentRateIndex == 0)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
    /* TODO : retry rate not in operation rate set */
    zm_msg1_tx(ZM_LV_0, "Not in operation rate set:", retryRate);
    return 1;

}