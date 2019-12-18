#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  u8_t ;
typedef  int u32_t ;
typedef  int u16_t ;
struct zsHpPriv {scalar_t__ dot11Mode; int* txop; int* cwmin; int* cwmax; } ;
struct TYPE_3__ {int EnableHT; } ;
struct TYPE_4__ {TYPE_1__ sta; struct zsHpPriv* hpPrivate; } ;

/* Variables and functions */
 scalar_t__ ZM_HAL_80211_MODE_STA ; 
 int /*<<< orphan*/  ZM_LV_0 ; 
 int /*<<< orphan*/  ZM_MAC_REG_AC0_CW ; 
 int /*<<< orphan*/  ZM_MAC_REG_AC1_AC0_AIFS ; 
 int /*<<< orphan*/  ZM_MAC_REG_AC1_AC0_TXOP ; 
 int /*<<< orphan*/  ZM_MAC_REG_AC1_CW ; 
 int /*<<< orphan*/  ZM_MAC_REG_AC2_CW ; 
 int /*<<< orphan*/  ZM_MAC_REG_AC3_AC2_AIFS ; 
 int /*<<< orphan*/  ZM_MAC_REG_AC3_AC2_TXOP ; 
 int /*<<< orphan*/  ZM_MAC_REG_AC3_CW ; 
 int /*<<< orphan*/  ZM_MAC_REG_AC4_CW ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zfDelayWriteInternalReg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zfFlushDelayWrite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zm_msg0_mm (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

u8_t zfHpUpdateQosParameter(zdev_t* dev, u16_t* cwminTbl, u16_t* cwmaxTbl,
        u16_t* aifsTbl, u16_t* txopTbl)
{
    struct zsHpPriv* hpPriv;

    zmw_get_wlan_dev(dev);
    hpPriv = wd->hpPrivate;

    zm_msg0_mm(ZM_LV_0, "zfHalUpdateQosParameter()");

    /* Note : Do not change cwmin for Q0 in Ad Hoc mode              */
    /*        otherwise driver will fail in Wifi beacon distribution */
    if (hpPriv->dot11Mode == ZM_HAL_80211_MODE_STA)
    {
#if 0 //Restore CWmin to improve down link throughput
        //cheating in BE traffic
        if (wd->sta.EnableHT == 1)
        {
            //cheating in BE traffic
            cwminTbl[0] = 7;//15;
        }
#endif
        cwmaxTbl[0] = 127;//1023;
        aifsTbl[0] = 2*9+10;//3 * 9 + 10;
    }

    /* CWMIN and CWMAX */
    zfDelayWriteInternalReg(dev, ZM_MAC_REG_AC0_CW, cwminTbl[0]
            + ((u32_t)cwmaxTbl[0]<<16));
    zfDelayWriteInternalReg(dev, ZM_MAC_REG_AC1_CW, cwminTbl[1]
            + ((u32_t)cwmaxTbl[1]<<16));
    zfDelayWriteInternalReg(dev, ZM_MAC_REG_AC2_CW, cwminTbl[2]
            + ((u32_t)cwmaxTbl[2]<<16));
    zfDelayWriteInternalReg(dev, ZM_MAC_REG_AC3_CW, cwminTbl[3]
            + ((u32_t)cwmaxTbl[3]<<16));
    zfDelayWriteInternalReg(dev, ZM_MAC_REG_AC4_CW, cwminTbl[4]
            + ((u32_t)cwmaxTbl[4]<<16));

    /* AIFS */
    zfDelayWriteInternalReg(dev, ZM_MAC_REG_AC1_AC0_AIFS, aifsTbl[0]
            +((u32_t)aifsTbl[0]<<12)+((u32_t)aifsTbl[0]<<24));
    zfDelayWriteInternalReg(dev, ZM_MAC_REG_AC3_AC2_AIFS, (aifsTbl[0]>>8)
            +((u32_t)aifsTbl[0]<<4)+((u32_t)aifsTbl[0]<<16));

    /* TXOP */
    zfDelayWriteInternalReg(dev, ZM_MAC_REG_AC1_AC0_TXOP, txopTbl[0]
            + ((u32_t)txopTbl[1]<<16));
    zfDelayWriteInternalReg(dev, ZM_MAC_REG_AC3_AC2_TXOP, txopTbl[2]
            + ((u32_t)txopTbl[3]<<16));

    zfFlushDelayWrite(dev);

    hpPriv->txop[0] = txopTbl[0];
    hpPriv->txop[1] = txopTbl[1];
    hpPriv->txop[2] = txopTbl[2];
    hpPriv->txop[3] = txopTbl[3];
    hpPriv->cwmin[0] = cwminTbl[0];
    hpPriv->cwmax[0] = cwmaxTbl[0];
    hpPriv->cwmin[1] = cwminTbl[1];
    hpPriv->cwmax[1] = cwmaxTbl[1];

    return 0;
}