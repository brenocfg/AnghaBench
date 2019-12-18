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
typedef  size_t u8_t ;
typedef  int u32_t ;
typedef  int u16_t ;
struct TYPE_5__ {TYPE_1__* staTable; } ;
struct TYPE_6__ {int frequency; TYPE_2__ ap; } ;
struct TYPE_4__ {size_t qosType; int /*<<< orphan*/  rcCell; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_LV_3 ; 
 TYPE_3__* wd ; 
 int* zcRateToPhyCtrl ; 
 int zfApFindSta (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ zfRateCtrlGetTxRate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  zm_msg2_mm (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

void zfApGetStaTxRateAndQosType(zdev_t* dev, u16_t* addr, u32_t* phyCtrl,
                                u8_t* qosType, u16_t* rcProbingFlag)
{
    u16_t id;
    u8_t rate;

    zmw_get_wlan_dev(dev);

    zmw_declare_for_critical_section();

    zmw_enter_critical_section(dev);

    if ((id = zfApFindSta(dev, addr)) != 0xffff)
    {
        rate = (u8_t)zfRateCtrlGetTxRate(dev, &wd->ap.staTable[id].rcCell, rcProbingFlag);
#ifdef ZM_AP_DEBUG
        //rate = 15;
#endif
        *phyCtrl = zcRateToPhyCtrl[rate];
        *qosType = wd->ap.staTable[id].qosType;
    }
    else
    {
        if (wd->frequency < 3000)
        {
            /* CCK 1M */
            //header[2] = 0x0f00;          //PHY control L
            //header[3] = 0x0000;          //PHY control H
            *phyCtrl = 0x00000F00;
        }
        else
        {
            /* CCK 6M */
            //header[2] = 0x0f01;          //PHY control L
            //header[3] = 0x000B;          //PHY control H
            *phyCtrl = 0x000B0F01;
        }
        *qosType = 0;
    }

    zmw_leave_critical_section(dev);

    zm_msg2_mm(ZM_LV_3, "PhyCtrl=", *phyCtrl);
    return;
}