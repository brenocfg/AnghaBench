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

/* Variables and functions */
 int /*<<< orphan*/  ZM_MAC_REG_SLOT_TIME ; 
 int /*<<< orphan*/  zfDelayWriteInternalReg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void zfHpSetSlotTimeRegister(zdev_t* dev, u8_t type)
{
    if(type == 0)
    {
        //normal slot = 20us
        zfDelayWriteInternalReg(dev, ZM_MAC_REG_SLOT_TIME, 20<<10);
    }
    else
    {
        //short slot = 9us
        zfDelayWriteInternalReg(dev, ZM_MAC_REG_SLOT_TIME, 9<<10);
    }
}