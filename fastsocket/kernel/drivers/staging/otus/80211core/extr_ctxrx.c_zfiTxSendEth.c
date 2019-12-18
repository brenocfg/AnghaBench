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
typedef  int /*<<< orphan*/  zbuf_t ;
typedef  int u16_t ;
struct TYPE_2__ {scalar_t__ wlanMode; int /*<<< orphan*/  tick; } ;

/* Variables and functions */
 int ZM_ERR_TX_PORT_DISABLED ; 
 int /*<<< orphan*/  ZM_EXTERNAL_ALLOC_BUF ; 
 int /*<<< orphan*/  ZM_LV_1 ; 
 int /*<<< orphan*/  ZM_LV_2 ; 
 scalar_t__ ZM_MODE_AP ; 
 scalar_t__ ZM_MODE_IBSS ; 
 scalar_t__ ZM_MODE_INFRASTRUCTURE ; 
 int /*<<< orphan*/  ZM_PERFORMANCE_TX_MSDU (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ZM_PORT_DISABLED ; 
 int ZM_SUCCESS ; 
 TYPE_1__* wd ; 
 int zfApBufferPsFrame (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ zfPowerSavingMgrIsSleeping (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfPowerSavingMgrWakeup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfPushVtxq (int /*<<< orphan*/ *) ; 
 int zfPutVtxq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ zfStaIbssPSQueueData (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zfTxPortControl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int zfTxSendEth (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfwBufFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zm_msg1_tx (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  zm_msg2_tx (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

u16_t zfiTxSendEth(zdev_t* dev, zbuf_t* buf, u16_t port)
{
    u16_t err, ret;

    zmw_get_wlan_dev(dev);

    ZM_PERFORMANCE_TX_MSDU(dev, wd->tick);
    zm_msg1_tx(ZM_LV_2, "zfiTxSendEth(), port=", port);
    /* Return error if port is disabled */
    if ((err = zfTxPortControl(dev, buf, port)) == ZM_PORT_DISABLED)
    {
        err = ZM_ERR_TX_PORT_DISABLED;
        goto zlError;
    }

#if 1
    if ((wd->wlanMode == ZM_MODE_AP) && (port < 0x20))
    {
        /* AP : Buffer frame for power saving STA */
        if ((ret = zfApBufferPsFrame(dev, buf, port)) == 1)
        {
            return ZM_SUCCESS;
        }
    }
    else
#endif
    if (wd->wlanMode == ZM_MODE_INFRASTRUCTURE)
    {
        if ( zfPowerSavingMgrIsSleeping(dev) )
        {
            /*check ZM_ENABLE_POWER_SAVE flag*/
            zfPowerSavingMgrWakeup(dev);
        }
    }
#ifdef ZM_ENABLE_IBSS_PS
    /* IBSS power-saving mode */
    else if ( wd->wlanMode == ZM_MODE_IBSS )
    {
        if ( zfStaIbssPSQueueData(dev, buf) )
        {
            return ZM_SUCCESS;
        }
    }
#endif

#if 1
    //if ( wd->bQoSEnable )
    if (1)
    {
        /* Put to VTXQ[ac] */
        ret = zfPutVtxq(dev, buf);

        /* Push VTXQ[ac] */
        zfPushVtxq(dev);
    }
    else
    {
        ret = zfTxSendEth(dev, buf, port, ZM_EXTERNAL_ALLOC_BUF, 0);
    }

    return ret;
#else
    return zfTxSendEth(dev, buf, port, ZM_EXTERNAL_ALLOC_BUF, 0);
#endif

zlError:
    zm_msg2_tx(ZM_LV_1, "Tx Comp err=", err);

    zfwBufFree(dev, buf, err);
    return err;
}