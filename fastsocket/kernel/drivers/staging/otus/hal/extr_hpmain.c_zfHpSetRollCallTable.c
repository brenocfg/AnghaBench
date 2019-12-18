#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int u64_t ;
typedef  int /*<<< orphan*/  u32_t ;
struct zsHpPriv {int camRollCallTable; } ;
struct TYPE_2__ {struct zsHpPriv* hpPrivate; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_MAC_REG_ROLL_CALL_TBL_H ; 
 int /*<<< orphan*/  ZM_MAC_REG_ROLL_CALL_TBL_L ; 
 TYPE_1__* wd ; 
 int /*<<< orphan*/  zfDelayWriteInternalReg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfFlushDelayWrite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfHpSetRollCallTable(zdev_t* dev)
{
    struct zsHpPriv* hpPriv;

    zmw_get_wlan_dev(dev);
    hpPriv=wd->hpPrivate;

    if (hpPriv->camRollCallTable != (u64_t) 0)
    {
        zfDelayWriteInternalReg(dev, ZM_MAC_REG_ROLL_CALL_TBL_L, (u32_t)(hpPriv->camRollCallTable & 0xffffffff));
        zfDelayWriteInternalReg(dev, ZM_MAC_REG_ROLL_CALL_TBL_H, (u32_t)((hpPriv->camRollCallTable >> 32) & 0xffffffff));
        zfFlushDelayWrite(dev);
    }
}