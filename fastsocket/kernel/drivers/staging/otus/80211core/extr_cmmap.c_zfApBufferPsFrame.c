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
typedef  scalar_t__ u16_t ;
struct TYPE_5__ {scalar_t__ staPowerSaving; int* bcmcTail; int* bcmcHead; int uniTail; int uniHead; int /*<<< orphan*/ ** uniArray; int /*<<< orphan*/  uapsdQ; TYPE_1__* staTable; int /*<<< orphan*/ *** bcmcArray; } ;
struct TYPE_6__ {TYPE_2__ ap; int /*<<< orphan*/  tick; } ;
struct TYPE_4__ {int psMode; int qosType; int qosInfo; } ;

/* Variables and functions */
 int ZM_BCMC_ARRAY_SIZE ; 
 int /*<<< orphan*/  ZM_ERR_AP_UAPSD_QUEUE_FULL ; 
 int /*<<< orphan*/  ZM_ERR_BCMC_PS_BUFFER_UNAVAILABLE ; 
 int /*<<< orphan*/  ZM_ERR_UNI_PS_BUFFER_UNAVAILABLE ; 
 int /*<<< orphan*/  ZM_LV_0 ; 
 scalar_t__ ZM_MAX_AP_SUPPORT ; 
 scalar_t__ ZM_SUCCESS ; 
 int ZM_UNI_ARRAY_SIZE ; 
 TYPE_3__* wd ; 
 int* zcUpToAc ; 
 scalar_t__ zfApFindSta (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ zfQueuePutNcs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfTxGetIpTosAndFrag (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,scalar_t__*) ; 
 int /*<<< orphan*/  zfwBufFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zm_msg0_tx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 
 scalar_t__ zmw_rx_buf_readh (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

u16_t zfApBufferPsFrame(zdev_t* dev, zbuf_t* buf, u16_t port)
{
    u16_t id;
    u16_t addr[3];
    u16_t vap = 0;
    u8_t up;
    u16_t fragOff;
    u8_t ac;
    u16_t ret;

    zmw_get_wlan_dev(dev);

    zmw_declare_for_critical_section();

    if (port < ZM_MAX_AP_SUPPORT)
    {
        vap = port;
    }

    addr[0] = zmw_rx_buf_readh(dev, buf, 0);
    addr[1] = zmw_rx_buf_readh(dev, buf, 2);
    addr[2] = zmw_rx_buf_readh(dev, buf, 4);

    if ((addr[0] & 0x1) == 0x1)
    {
        if (wd->ap.staPowerSaving > 0)
        {
            zmw_enter_critical_section(dev);

            /* Buffer this BC or MC frame */
            if (((wd->ap.bcmcTail[vap]+1)&(ZM_BCMC_ARRAY_SIZE-1))
                    != wd->ap.bcmcHead[vap])
            {
                wd->ap.bcmcArray[vap][wd->ap.bcmcTail[vap]++] = buf;
                wd->ap.bcmcTail[vap] &= (ZM_BCMC_ARRAY_SIZE-1);
                zmw_leave_critical_section(dev);

                zm_msg0_tx(ZM_LV_0, "Buffer BCMC");
            }
            else
            {
                /* bcmcArray full */
                zmw_leave_critical_section(dev);

                zm_msg0_tx(ZM_LV_0, "BCMC buffer full");

                /* free buffer according to buffer type */
                zfwBufFree(dev, buf, ZM_ERR_BCMC_PS_BUFFER_UNAVAILABLE);
            }
            return 1;
        }
    }
    else
    {
        zmw_enter_critical_section(dev);

        if ((id = zfApFindSta(dev, addr)) != 0xffff)
        {
            if (wd->ap.staTable[id].psMode == 1)
            {

                zfTxGetIpTosAndFrag(dev, buf, &up, &fragOff);
                ac = zcUpToAc[up&0x7] & 0x3;

                if ((wd->ap.staTable[id].qosType == 1) &&
                        ((wd->ap.staTable[id].qosInfo & (0x8>>ac)) != 0))
                {
                    ret = zfQueuePutNcs(dev, wd->ap.uapsdQ, buf, wd->tick);
                    zmw_leave_critical_section(dev);
                    if (ret != ZM_SUCCESS)
                    {
                        zfwBufFree(dev, buf, ZM_ERR_AP_UAPSD_QUEUE_FULL);
                    }
                }
                else
                {
                /* Buffer this unicast frame */
                if (((wd->ap.uniTail+1)&(ZM_UNI_ARRAY_SIZE-1))
                        != wd->ap.uniHead)
                {
                    wd->ap.uniArray[wd->ap.uniTail++] = buf;
                    wd->ap.uniTail &= (ZM_UNI_ARRAY_SIZE-1);
                    zmw_leave_critical_section(dev);
                    zm_msg0_tx(ZM_LV_0, "Buffer UNI");

                }
                else
                {
                    /* uniArray full */
                    zmw_leave_critical_section(dev);
                    zm_msg0_tx(ZM_LV_0, "UNI buffer full");
                    /* free buffer according to buffer type */
                    zfwBufFree(dev, buf, ZM_ERR_UNI_PS_BUFFER_UNAVAILABLE);
                }
                }
                return 1;
            } /* if (wd->ap.staTable[id++].psMode == 1) */
        } /* if ((id = zfApFindSta(dev, addr)) != 0xffff) */
        zmw_leave_critical_section(dev);
    }

    return 0;
}