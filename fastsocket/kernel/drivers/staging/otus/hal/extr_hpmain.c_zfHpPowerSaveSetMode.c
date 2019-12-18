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
typedef  int /*<<< orphan*/  zdev_t ;
typedef  scalar_t__ u8_t ;
typedef  int u16_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_MAC_REG_BCN_PERIOD ; 
 int /*<<< orphan*/  ZM_MAC_REG_PRETBTT ; 
 int /*<<< orphan*/  zfDelayWriteInternalReg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zfFlushDelayWrite (int /*<<< orphan*/ *) ; 

void zfHpPowerSaveSetMode(zdev_t* dev, u8_t staMode, u8_t psMode, u16_t bcnInterval)
{
    if ( staMode == 0 )
    {
        if ( psMode == 0 )
        {
            // Turn off pre-TBTT interrupt
            zfDelayWriteInternalReg(dev, ZM_MAC_REG_PRETBTT, 0);
            zfDelayWriteInternalReg(dev, ZM_MAC_REG_BCN_PERIOD, 0);
            zfFlushDelayWrite(dev);
        }
        else
        {
            // Turn on pre-TBTT interrupt
            zfDelayWriteInternalReg(dev, ZM_MAC_REG_PRETBTT, (bcnInterval-6)<<16);
            zfDelayWriteInternalReg(dev, ZM_MAC_REG_BCN_PERIOD, bcnInterval);
            zfFlushDelayWrite(dev);
        }
    }
}