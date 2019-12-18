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
struct TYPE_5__ {int /*<<< orphan*/  txUnicastFrm; } ;
struct TYPE_4__ {int* bssid; scalar_t__ wmeConnected; } ;
struct TYPE_6__ {scalar_t__ wlanMode; TYPE_2__ commTally; TYPE_1__ sta; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_INTERNAL_ALLOC_BUF ; 
 int /*<<< orphan*/  ZM_LV_0 ; 
 scalar_t__ ZM_MODE_IBSS ; 
 scalar_t__ ZM_MODE_INFRASTRUCTURE ; 
 int ZM_SUCCESS ; 
 int /*<<< orphan*/  ZM_WLAN_FRAME_TYPE_NULL ; 
 int /*<<< orphan*/  ZM_WLAN_FRAME_TYPE_QOS_NULL ; 
 TYPE_3__* wd ; 
 int zfHpSend (int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int zfTxGenMmHeader (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zfwBufAllocate (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zfwBufFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfwBufSetSize (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zm_msg0_mm (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfSendNullData(zdev_t* dev, u8_t type)
{
    zbuf_t* buf;
    //u16_t addrTblSize;
    //struct zsAddrTbl addrTbl;
    u16_t err;
    u16_t hlen;
    u16_t header[(34+8+1)/2];
    u16_t bcastAddr[3] = {0xffff,0xffff,0xffff};
    u16_t *dstAddr;

    zmw_get_wlan_dev(dev);

    if ((buf = zfwBufAllocate(dev, 1024)) == NULL)
    {
        zm_msg0_mm(ZM_LV_0, "Alloc mm buf Fail!");
        return;
    }

    zfwBufSetSize(dev, buf, 0);

    //zm_msg2_mm(ZM_LV_2, "buf->len=", buf->len);

    if ( wd->wlanMode == ZM_MODE_IBSS)
    {
        dstAddr = bcastAddr;
    }
    else
    {
        dstAddr = wd->sta.bssid;
    }

    if (wd->sta.wmeConnected != 0)
    {
        /* If connect to a WMM AP, Send QoS Null data */
        hlen = zfTxGenMmHeader(dev, ZM_WLAN_FRAME_TYPE_QOS_NULL, dstAddr, header, 0, buf, 0, 0);
    }
    else
    {
        hlen = zfTxGenMmHeader(dev, ZM_WLAN_FRAME_TYPE_NULL, dstAddr, header, 0, buf, 0, 0);
    }

    if (wd->wlanMode == ZM_MODE_INFRASTRUCTURE)
    {
        header[4] |= 0x0100; //TODS bit
    }

    if ( type == 1 )
    {
        header[4] |= 0x1000;
    }

    /* Get buffer DMA address */
    //if ((addrTblSize = zfwBufMapDma(dev, buf, &addrTbl)) == 0)
    //if ((addrTblSize = zfwMapTxDma(dev, buf, &addrTbl)) == 0)
    //{
    //    goto zlError;
    //}

    /*increase unicast frame counter*/
    wd->commTally.txUnicastFrm++;

    if ((err = zfHpSend(dev, header, hlen, NULL, 0, NULL, 0, buf, 0,
            ZM_INTERNAL_ALLOC_BUF, 0, 0xff)) != ZM_SUCCESS)
    {
        goto zlError;
    }


    return;

zlError:

    zfwBufFree(dev, buf, 0);
    return;

}