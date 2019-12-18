#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  size_t u8_t ;
typedef  int /*<<< orphan*/  u32_t ;
typedef  int /*<<< orphan*/  u16_t ;
struct TYPE_6__ {size_t oppositeCount; TYPE_1__* oppositeInfo; } ;
struct TYPE_8__ {scalar_t__ wlanMode; TYPE_2__ sta; } ;
struct TYPE_7__ {size_t* operationRateSet; } ;
struct TYPE_5__ {TYPE_3__ rcCell; int /*<<< orphan*/  macAddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_MAC_WORD_TO_BYTE (int /*<<< orphan*/ *,size_t*) ; 
 scalar_t__ ZM_MODE_INFRASTRUCTURE ; 
 TYPE_4__* wd ; 
 int /*<<< orphan*/ * zcRateToPhyCtrl ; 
 scalar_t__ zfMemoryIsEqual (size_t*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ zfRateCtrlGetTxRate (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

void zfStaGetTxRate(zdev_t* dev, u16_t* macAddr, u32_t* phyCtrl,
        u16_t* rcProbingFlag)
{
    u8_t   addr[6], i;
    u8_t   rate;
    zmw_get_wlan_dev(dev);
    zmw_declare_for_critical_section();

    ZM_MAC_WORD_TO_BYTE(macAddr, addr);
    *phyCtrl = 0;

    if ( wd->wlanMode == ZM_MODE_INFRASTRUCTURE )
    {
        zmw_enter_critical_section(dev);
        rate = (u8_t)zfRateCtrlGetTxRate(dev, &wd->sta.oppositeInfo[0].rcCell, rcProbingFlag);
//#ifdef ZM_FB50
        //rate = 27;
//#endif
        *phyCtrl = zcRateToPhyCtrl[rate];
        zmw_leave_critical_section(dev);
    }
    else
    {
        zmw_enter_critical_section(dev);
        for(i=0; i<wd->sta.oppositeCount; i++)
        {
            if ( addr[0] && 0x01 == 1 ) // The default beacon transmitted rate is CCK and 1 Mbps , but the a mode should use
                                        // OFDM modulation and 6Mbps to transmit beacon.
            {
                //rate = (u8_t)zfRateCtrlGetTxRate(dev, &wd->sta.oppositeInfo[i].rcCell, rcProbingFlag);
                rate = wd->sta.oppositeInfo[i].rcCell.operationRateSet[0];
                *phyCtrl = zcRateToPhyCtrl[rate];
                break;
            }
            else if ( zfMemoryIsEqual(addr, wd->sta.oppositeInfo[i].macAddr, 6) )
            {
                rate = (u8_t)zfRateCtrlGetTxRate(dev, &wd->sta.oppositeInfo[i].rcCell, rcProbingFlag);
                *phyCtrl = zcRateToPhyCtrl[rate];
                break;
            }
        }
        zmw_leave_critical_section(dev);
    }

    return;
}