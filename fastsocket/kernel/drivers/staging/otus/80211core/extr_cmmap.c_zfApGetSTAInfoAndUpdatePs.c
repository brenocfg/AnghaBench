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
typedef  int /*<<< orphan*/  zbuf_t ;
typedef  int u8_t ;
typedef  int u16_t ;
struct TYPE_5__ {int /*<<< orphan*/  uapsdQ; TYPE_1__* staTable; int /*<<< orphan*/  staPowerSaving; } ;
struct TYPE_6__ {TYPE_2__ ap; int /*<<< orphan*/  tick; } ;
struct TYPE_4__ {scalar_t__ psMode; int qosType; int qosInfo; int vap; int state; int /*<<< orphan*/  time; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_EXTERNAL_ALLOC_BUF ; 
 int /*<<< orphan*/  ZM_LV_0 ; 
 TYPE_3__* wd ; 
 int zfApFindSta (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * zfQueueGetWithMac (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  zfTxSendEth (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zm_msg0_mm (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

u16_t zfApGetSTAInfoAndUpdatePs(zdev_t* dev, u16_t* addr, u16_t* state,
                                u8_t* vap, u16_t psMode, u8_t* uapsdTrig)
{
    u16_t id;
    u8_t uapsdStaAwake = 0;

    zmw_get_wlan_dev(dev);

    zmw_declare_for_critical_section();

    zmw_enter_critical_section(dev);

#ifdef ZM_AP_DEBUG
    //psMode=0;
#endif

    if ((id = zfApFindSta(dev, addr)) != 0xffff)
    {
        if (psMode != 0)
        {
            zm_msg0_mm(ZM_LV_0, "psMode = 1");
            if (wd->ap.staTable[id].psMode == 0)
            {
                wd->ap.staPowerSaving++;
            }
            else
            {
                if (wd->ap.staTable[id].qosType == 1)
                {
                    zm_msg0_mm(ZM_LV_0, "UAPSD trigger");
                    *uapsdTrig = wd->ap.staTable[id].qosInfo;
                }
            }
        }
        else
        {
            if (wd->ap.staTable[id].psMode != 0)
            {
                wd->ap.staPowerSaving--;
                if ((wd->ap.staTable[id].qosType == 1) && ((wd->ap.staTable[id].qosInfo&0xf)!=0))
                {
                    uapsdStaAwake = 1;
                }
            }
        }

        wd->ap.staTable[id].psMode = (u8_t) psMode;
        wd->ap.staTable[id].time = wd->tick;
        *vap = wd->ap.staTable[id].vap;
        *state = wd->ap.staTable[id++].state;
    }

    zmw_leave_critical_section(dev);

    if (uapsdStaAwake == 1)
    {
        zbuf_t* psBuf;
        u8_t mb;

        while (1)
        {
            if ((psBuf = zfQueueGetWithMac(dev, wd->ap.uapsdQ, (u8_t*)addr, &mb)) != NULL)
            {
                zfTxSendEth(dev, psBuf, 0, ZM_EXTERNAL_ALLOC_BUF, 0);
            }
            else
            {
                break;
            }
        }
    }

    return id;
}