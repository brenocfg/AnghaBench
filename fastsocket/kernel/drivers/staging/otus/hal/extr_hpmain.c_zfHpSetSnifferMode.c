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
typedef  scalar_t__ u16_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_MAC_REG_SNIFFER ; 
 int /*<<< orphan*/  zfDelayWriteInternalReg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zfFlushDelayWrite (int /*<<< orphan*/ *) ; 

u16_t zfHpSetSnifferMode(zdev_t* dev, u16_t on)
{
    if (on != 0)
    {
        zfDelayWriteInternalReg(dev, ZM_MAC_REG_SNIFFER, 0x2000001);
    }
    else
    {
        zfDelayWriteInternalReg(dev, ZM_MAC_REG_SNIFFER, 0x2000000);
    }
    zfFlushDelayWrite(dev);
    return 0;
}