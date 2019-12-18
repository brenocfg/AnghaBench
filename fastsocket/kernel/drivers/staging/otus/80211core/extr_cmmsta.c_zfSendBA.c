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
typedef  int /*<<< orphan*/  zbuf_t ;
typedef  int /*<<< orphan*/  u8_t ;
typedef  int u16_t ;
struct TYPE_3__ {int /*<<< orphan*/  bssid; } ;
struct TYPE_4__ {TYPE_1__ sta; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_INTERNAL_ALLOC_BUF ; 
 int /*<<< orphan*/  ZM_LV_0 ; 
 int ZM_SUCCESS ; 
 int /*<<< orphan*/  ZM_WLAN_FRAME_TYPE_BA ; 
 TYPE_2__* wd ; 
 int* zcRateToPhyCtrl ; 
 int zfHpSend (int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zfTxGenMmHeader (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zfwBufAllocate (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zfwBufFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfwBufSetSize (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zm_msg0_mm (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_tx_buf_writeb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zmw_tx_buf_writeh (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 

void zfSendBA(zdev_t* dev, u16_t start_seq, u8_t *bitmap)
{
    zbuf_t* buf;
    //u16_t addrTblSize;
    //struct zsAddrTbl addrTbl;
    u16_t err;
    u16_t hlen;
    u16_t header[(8+24+1)/2];
    u16_t i, offset = 0;

    zmw_get_wlan_dev(dev);

    if ((buf = zfwBufAllocate(dev, 1024)) == NULL)
    {
        zm_msg0_mm(ZM_LV_0, "Alloc mm buf Fail!");
        return;
    }

    zfwBufSetSize(dev, buf, 12); // 28 = FC 2 + DU 2 + RA 6 + TA 6 + BAC 2 + SEQ 2 + BitMap 8
                                 // 12 = BAC 2 + SEQ 2 + BitMap 8

    //zm_msg2_mm(ZM_LV_2, "buf->len=", buf->len);

    zfTxGenMmHeader(dev, ZM_WLAN_FRAME_TYPE_BA, wd->sta.bssid, header, 0, buf, 0, 0);

    header[0] = 32; /* MAC header 16 + BA control 2 + BA info 10 + FCS 4*/
    header[1] = 0x4;  /* No ACK */

    /* send by OFDM 6M */
    header[2] = (u16_t)(zcRateToPhyCtrl[4] & 0xffff);
    header[3] = (u16_t)(zcRateToPhyCtrl[4]>>16) & 0xffff;

    hlen = 16 + 8;  /* MAC header 16 + control 8*/
    offset = 0;
    zmw_tx_buf_writeh(dev, buf, offset, 0x05); /*compressed bitmap on*/
    offset+=2;
    zmw_tx_buf_writeh(dev, buf, offset, start_seq);
    offset+=2;

    for (i=0; i<8; i++) {
        zmw_tx_buf_writeb(dev, buf, offset, bitmap[i]);
        offset++;
    }

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