#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  u8_t ;
typedef  int u32_t ;
typedef  int /*<<< orphan*/  u16_t ;
struct zsBssInfo {scalar_t__* extSupportedRates; int frequency; int EnableHT; int /*<<< orphan*/  SG40; int /*<<< orphan*/ * macaddr; } ;
struct TYPE_5__ {TYPE_1__* oppositeInfo; } ;
struct TYPE_6__ {TYPE_2__ sta; } ;
struct TYPE_4__ {int /*<<< orphan*/  rcCell; int /*<<< orphan*/ * macAddr; } ;

/* Variables and functions */
 int ZM_HP_CAP_11N_ONE_TX_STREAM ; 
 TYPE_3__* wd ; 
 int zfHpCapability (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfMemoryCopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zfRateCtrlInitCell (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int zfStaFindFreeOpposite (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  zfStaInitCommonOppositeInfo (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

int zfStaSetOppositeInfoFromBSSInfo(zdev_t* dev, struct zsBssInfo* pBssInfo)
{
    int i;
    u8_t*  dst;
    u16_t  sa[3];
    int res;
    u32_t oneTxStreamCap;

    zmw_get_wlan_dev(dev);

    zfMemoryCopy((u8_t*) sa, pBssInfo->macaddr, 6);

    res = zfStaFindFreeOpposite(dev, sa, &i);
    if ( res != 0 )
    {
        goto zlReturn;
    }

    dst = wd->sta.oppositeInfo[i].macAddr;
    zfMemoryCopy(dst, (u8_t *)sa, 6);

    oneTxStreamCap = (zfHpCapability(dev) & ZM_HP_CAP_11N_ONE_TX_STREAM);

    if (pBssInfo->extSupportedRates[1] != 0)
    {
        /* TODO : Handle 11n */
        if (pBssInfo->frequency < 3000)
        {
            /* 2.4GHz */
            if (pBssInfo->EnableHT == 1)
                zfRateCtrlInitCell(dev, &wd->sta.oppositeInfo[i].rcCell, (oneTxStreamCap!=0)?3:2, 1, pBssInfo->SG40);
            else
                zfRateCtrlInitCell(dev, &wd->sta.oppositeInfo[i].rcCell, 1, 1, pBssInfo->SG40);
        }
        else
        {
            /* 5GHz */
            if (pBssInfo->EnableHT == 1)
                zfRateCtrlInitCell(dev, &wd->sta.oppositeInfo[i].rcCell, (oneTxStreamCap!=0)?3:2, 0, pBssInfo->SG40);
            else
                zfRateCtrlInitCell(dev, &wd->sta.oppositeInfo[i].rcCell, 1, 0, pBssInfo->SG40);
        }
    }
    else
    {
        /* TODO : Handle 11n */
        if (pBssInfo->frequency < 3000)
        {
            /* 2.4GHz */
            if (pBssInfo->EnableHT == 1)
                zfRateCtrlInitCell(dev, &wd->sta.oppositeInfo[i].rcCell, (oneTxStreamCap!=0)?3:2, 1, pBssInfo->SG40);
            else
                zfRateCtrlInitCell(dev, &wd->sta.oppositeInfo[i].rcCell, 0, 1, pBssInfo->SG40);
        }
        else
        {
            /* 5GHz */
            if (pBssInfo->EnableHT == 1)
                zfRateCtrlInitCell(dev, &wd->sta.oppositeInfo[i].rcCell, (oneTxStreamCap!=0)?3:2, 0, pBssInfo->SG40);
            else
                zfRateCtrlInitCell(dev, &wd->sta.oppositeInfo[i].rcCell, 1, 0, pBssInfo->SG40);
        }
    }


    zfStaInitCommonOppositeInfo(dev, i);
zlReturn:
    return 0;
}