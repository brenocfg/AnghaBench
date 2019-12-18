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

/* Variables and functions */
 int /*<<< orphan*/  zfDelayWriteInternalReg (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  zfFlushDelayWrite (int /*<<< orphan*/ *) ; 

void zfDbgCloseEeprom(zdev_t* dev)
{
    // lock EEPROM
    zfDelayWriteInternalReg(dev, 0x1D1400, 0x87654321);
    //zfDelayWriteInternalReg(dev, 0x1D1404, 0xffffffff);
    //zfDelayWriteInternalReg(dev, 0x1D1408, 0xffffffff);
    //zfDelayWriteInternalReg(dev, 0x1D1414, 0x100);
    zfFlushDelayWrite(dev);
}