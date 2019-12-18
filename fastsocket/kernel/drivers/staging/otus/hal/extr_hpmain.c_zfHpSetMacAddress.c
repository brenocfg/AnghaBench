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
typedef  int u32_t ;
typedef  int u16_t ;

/* Variables and functions */
 scalar_t__ ZM_MAC_REG_ACK_TABLE ; 
 scalar_t__ ZM_MAC_REG_MAC_ADDR_H ; 
 scalar_t__ ZM_MAC_REG_MAC_ADDR_L ; 
 int /*<<< orphan*/  zfDelayWriteInternalReg (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  zfFlushDelayWrite (int /*<<< orphan*/ *) ; 

void zfHpSetMacAddress(zdev_t* dev, u16_t* macAddr, u16_t macAddrId)
{
    if (macAddrId == 0)
    {
        zfDelayWriteInternalReg(dev, ZM_MAC_REG_MAC_ADDR_L,
                (((u32_t)macAddr[1])<<16) | macAddr[0]);
        zfDelayWriteInternalReg(dev, ZM_MAC_REG_MAC_ADDR_H, macAddr[2]);
    }
    else if (macAddrId <= 7)
    {
        zfDelayWriteInternalReg(dev, ZM_MAC_REG_ACK_TABLE+((macAddrId-1)*8),
                macAddr[0] + ((u32_t)macAddr[1]<<16));
        zfDelayWriteInternalReg(dev, ZM_MAC_REG_ACK_TABLE+((macAddrId-1)*8)+4,
                macAddr[2]);
    }
    zfFlushDelayWrite(dev);
}