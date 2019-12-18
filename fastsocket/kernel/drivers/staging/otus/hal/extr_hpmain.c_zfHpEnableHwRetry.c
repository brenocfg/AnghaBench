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
typedef  int /*<<< orphan*/  u16_t ;

/* Variables and functions */
 int /*<<< orphan*/  zfDelayWriteInternalReg (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  zfFlushDelayWrite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfFwRetry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

u16_t zfHpEnableHwRetry(zdev_t* dev)
{
    u16_t ret;

    ret = zfFwRetry(dev, 0);

    zfDelayWriteInternalReg(dev, 0x1c3b28, 0x33333);
    zfFlushDelayWrite(dev);

    return ret;
}