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
typedef  int u8_t ;
typedef  scalar_t__ u32_t ;

/* Variables and functions */
 scalar_t__ ZM_CH_G_14 ; 
 int /*<<< orphan*/  ZM_MAC_REG_DYNAMIC_SIFS_ACK ; 
 int /*<<< orphan*/  zfDelayWriteInternalReg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zfFlushDelayWrite (int /*<<< orphan*/ *) ; 

void zfSelAdcClk(zdev_t* dev, u8_t bw40, u32_t frequency)
{
    if(bw40 == 1)
    {
        //zfDelayWriteInternalReg(dev, 0x1D4008, 0x73);
        zfDelayWriteInternalReg(dev, ZM_MAC_REG_DYNAMIC_SIFS_ACK, 0x10A);
        zfFlushDelayWrite(dev);
    }
    else
    {
        //zfDelayWriteInternalReg(dev, 0x1D4008, 0x70);
        if ( frequency <= ZM_CH_G_14 )
        {
            zfDelayWriteInternalReg(dev, ZM_MAC_REG_DYNAMIC_SIFS_ACK, 0x105);
        }
        else
        {
            zfDelayWriteInternalReg(dev, ZM_MAC_REG_DYNAMIC_SIFS_ACK, 0x104);
        }
        zfFlushDelayWrite(dev);
    }
}