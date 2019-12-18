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
typedef  int u32_t ;

/* Variables and functions */
 int ZM_MPDU_DENSITY_8US ; 
 int /*<<< orphan*/  zfDelayWriteInternalReg (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  zfFlushDelayWrite (int /*<<< orphan*/ *) ; 

void zfHpSetMPDUDensity(zdev_t* dev, u8_t density)
{
    u32_t value;

    if (density > ZM_MPDU_DENSITY_8US)
    {
        return;
    }

    /* Default value in this register */
    value = 0x140A00 | density;

    zfDelayWriteInternalReg(dev, 0x1c3ba0, value);
    zfFlushDelayWrite(dev);
    return;
}