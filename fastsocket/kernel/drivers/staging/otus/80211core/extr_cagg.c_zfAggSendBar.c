#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  zbuf_t ;
typedef  int /*<<< orphan*/  u8_t ;
typedef  int u16_t ;
struct aggBarControl {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dst; } ;
typedef  TYPE_1__* TID_TX ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_INTERNAL_ALLOC_BUF ; 
 int /*<<< orphan*/  ZM_LV_0 ; 
 int ZM_SUCCESS ; 
 int err ; 
 int /*<<< orphan*/  zfAggGenBarHeader (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int zfAggSetBarBody (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_1__*,struct aggBarControl*) ; 
 int zfHpSend (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zfPushVtxq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfPutVmmq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zfwBufAllocate (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zfwBufSetSize (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zm_msg0_mm (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zmw_tx_buf_writeh (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 

u16_t   zfAggSendBar(zdev_t* dev, TID_TX tid_tx, struct aggBarControl *aggBarControl)
{
    zbuf_t* buf;
    //u16_t addrTblSize;
    //struct zsAddrTbl addrTbl;
    //u16_t err;
    u16_t offset = 0;
    u16_t hlen = 16+8;  /* mac header + control headers*/
    u16_t header[(8+24+1)/2];
    u16_t vap = 0;
    u16_t i;
    u8_t encrypt = 0;

    //zmw_get_wlan_dev(dev);

    //zmw_declare_for_critical_section();


    /*
     * TBD : Maximum size of management frame
     */
    if ((buf = zfwBufAllocate(dev, 1024)) == NULL)
    {
        zm_msg0_mm(ZM_LV_0, "Alloc mm buf Fail!");
        return ZM_SUCCESS;
    }

    /*
     * Reserve room for wlan header
     */
    offset = hlen;

    /*
     * add addba frame body
     */
    offset = zfAggSetBarBody(dev, buf, offset, tid_tx, aggBarControl);


    zfwBufSetSize(dev, buf, offset);

    /*
     * Copy wlan header
     */
    zfAggGenBarHeader(dev, tid_tx->dst, header, offset-hlen, buf, vap, encrypt);
    for (i=0; i<(hlen>>1); i++)
    {
        zmw_tx_buf_writeh(dev, buf, i*2, header[i]);
    }

    /* Get buffer DMA address */
    //if ((addrTblSize = zfwBufMapDma(dev, buf, &addrTbl)) == 0)
    //if ((addrTblSize = zfwMapTxDma(dev, buf, &addrTbl)) == 0)
    //{
    //    goto zlError;
    //}

    //zm_msg2_mm(ZM_LV_2, "offset=", offset);
    //zm_msg2_mm(ZM_LV_2, "hlen=", hlen);
    //zm_msg2_mm(ZM_LV_2, "addrTblSize=", addrTblSize);
    //zm_msg2_mm(ZM_LV_2, "addrTbl.len[0]=", addrTbl.len[0]);
    //zm_msg2_mm(ZM_LV_2, "addrTbl.physAddrl[0]=", addrTbl.physAddrl[0]);
    //zm_msg2_mm(ZM_LV_2, "buf->data=", buf->data);

    #if 0
    if ((err = zfHpSend(dev, NULL, 0, NULL, 0, NULL, 0, buf, 0,
            ZM_INTERNAL_ALLOC_BUF, 0, 0xff)) != ZM_SUCCESS)
    {
        goto zlError;
    }
    #else
    zfPutVmmq(dev, buf);
    zfPushVtxq(dev);
    #endif

    return ZM_SUCCESS;

}