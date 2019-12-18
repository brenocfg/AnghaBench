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
struct TYPE_4__ {int isSleepAllowed; int sleepAllowedtick; scalar_t__ tempWakeUp; int /*<<< orphan*/  state; } ;
struct TYPE_5__ {int powerSaveMode; int aid; int qosInfo; int /*<<< orphan*/  uapsdQ; TYPE_1__ psMgr; } ;
struct TYPE_6__ {TYPE_2__ sta; } ;

/* Variables and functions */
 int ZM_BIT_0 ; 
 int /*<<< orphan*/  ZM_EXTERNAL_ALLOC_BUF ; 
 int /*<<< orphan*/  ZM_PS_MSG_STATE_S1 ; 
#define  ZM_STA_PS_FAST 130 
#define  ZM_STA_PS_LIGHT 129 
#define  ZM_STA_PS_MAX 128 
 int ZM_STA_PS_NONE ; 
 int /*<<< orphan*/  ZM_WLAN_EID_TIM ; 
 TYPE_3__* wd ; 
 int zfFindElement (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfPowerSavingMgrMain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zfQueueGet (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfSendNullData (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfSendPSPoll (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfTxSendEth (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zm_debug_msg0 (char*) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 
 int zmw_rx_buf_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void zfPowerSavingMgrProcessBeacon(zdev_t* dev, zbuf_t* buf)
{
    u8_t   length, bitmap;
    u16_t  offset, n1, n2, q, r;
    zbuf_t* psBuf;

    zmw_get_wlan_dev(dev);
    zmw_declare_for_critical_section();

    if ( wd->sta.powerSaveMode == ZM_STA_PS_NONE  )
    //if ( wd->sta.psMgr.state != ZM_PS_MSG_STATE_SLEEP )
    {
        return;
    }

    wd->sta.psMgr.isSleepAllowed = 1;

    if ( (offset=zfFindElement(dev, buf, ZM_WLAN_EID_TIM)) != 0xffff )
    {
        length = zmw_rx_buf_readb(dev, buf, offset+1);

        if ( length > 3 )
        {
            n1 = zmw_rx_buf_readb(dev, buf, offset+4) & (~ZM_BIT_0);
            n2 = length + n1 - 4;
            q = wd->sta.aid >> 3;
            r = wd->sta.aid & 7;

            if ((q >= n1) && (q <= n2))
            {
                bitmap = zmw_rx_buf_readb(dev, buf, offset+5+q-n1);

                if ( (bitmap >> r) &  ZM_BIT_0 )
                {
                    //if ( wd->sta.powerSaveMode == ZM_STA_PS_FAST )
                    if ( 0 )
                    {
                        wd->sta.psMgr.state = ZM_PS_MSG_STATE_S1;
                        //zfSendPSPoll(dev);
                        zfSendNullData(dev, 0);
                    }
                    else
                    {
                        if ((wd->sta.qosInfo&0xf) != 0xf)
                        {
                            /* send ps-poll */
                            //printk("zfSendPSPoll #1\n");

                            wd->sta.psMgr.isSleepAllowed = 0;

                            switch (wd->sta.powerSaveMode)
                            {
                            case ZM_STA_PS_MAX:
                            case ZM_STA_PS_FAST:
                                //zm_debug_msg0("wake up and send PS-Poll\n");
                                zfSendPSPoll(dev);
                                break;
                            case ZM_STA_PS_LIGHT:
                                zm_debug_msg0("wake up and send null data\n");

                                zmw_enter_critical_section(dev);
                                wd->sta.psMgr.sleepAllowedtick = 400;
                                zmw_leave_critical_section(dev);

                                zfSendNullData(dev, 0);
                                break;
                            }

                            wd->sta.psMgr.tempWakeUp = 0;
                        }
                    }
                }
            }
        }
    }

    while ((psBuf = zfQueueGet(dev, wd->sta.uapsdQ)) != NULL)
    {
        zfTxSendEth(dev, psBuf, 0, ZM_EXTERNAL_ALLOC_BUF, 0);
    }

    //printk("zfPowerSavingMgrProcessBeacon #1\n");
    zfPowerSavingMgrMain(dev);
}