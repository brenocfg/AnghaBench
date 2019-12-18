#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  zbuf_t ;
typedef  scalar_t__ u8_t ;
typedef  int u16_t ;

/* Variables and functions */
 int ZM_ERR_TX_PORT_DISABLED ; 
 int /*<<< orphan*/  ZM_INTERNAL_ALLOC_BUF ; 
 int /*<<< orphan*/  ZM_LV_1 ; 
 int /*<<< orphan*/  ZM_LV_2 ; 
 int ZM_PORT_DISABLED ; 
 int /*<<< orphan*/  ZM_RX_FRAME_SIZE ; 
 int ZM_STATE_ASOC ; 
 int ZM_WLAN_HEADER_A1_OFFSET ; 
 int ZM_WLAN_HEADER_A2_OFFSET ; 
 int ZM_WLAN_HEADER_A3_OFFSET ; 
 int zfApBufferPsFrame (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int zfApGetSTAInfo (int /*<<< orphan*/ *,int*,int*,scalar_t__*) ; 
 int /*<<< orphan*/  zfPushVtxq (int /*<<< orphan*/ *) ; 
 int zfPutVtxq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zfTxPortControl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  zfTxSendEth (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zfwBufAllocate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfwBufFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int zfwBufGetSize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfwBufSetSize (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zm_msg0_rx (int /*<<< orphan*/ ,char*) ; 
 int zmw_rx_buf_readh (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zmw_tx_buf_writeh (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 

u16_t zfIntrabssForward(zdev_t* dev, zbuf_t* buf, u8_t srcVap)
{
    u16_t err;
    u16_t asocFlag = 0;
    u16_t dst[3];
    u16_t aid;
    u16_t staState;
    zbuf_t* txBuf;
    u16_t len;
    u16_t i;
    u16_t temp;
    u16_t ret;
    u8_t vap = 0;
#ifdef ZM_ENABLE_NATIVE_WIFI
    dst[0] = zmw_rx_buf_readh(dev, buf, ZM_WLAN_HEADER_A3_OFFSET);
    dst[1] = zmw_rx_buf_readh(dev, buf, ZM_WLAN_HEADER_A3_OFFSET+2);
    dst[2] = zmw_rx_buf_readh(dev, buf, ZM_WLAN_HEADER_A3_OFFSET+4);
#else
    dst[0] = zmw_rx_buf_readh(dev, buf, 0);
    dst[1] = zmw_rx_buf_readh(dev, buf, 2);
    dst[2] = zmw_rx_buf_readh(dev, buf, 4);
#endif  // ZM_ENABLE_NATIVE_WIFI

    /* Do Intra-BSS forward(data copy) if necessary*/
    if ((dst[0]&0x1) != 0x1)
    {
        aid = zfApGetSTAInfo(dev, dst, &staState, &vap);
        if ((aid != 0xffff) && (staState == ZM_STATE_ASOC) && (srcVap == vap))
        {
            asocFlag = 1;
            zm_msg0_rx(ZM_LV_2, "Intra-BSS forward : asoc STA");
        }

    }
    else
    {
        vap = srcVap;
        zm_msg0_rx(ZM_LV_2, "Intra-BSS forward : BCorMC");
    }

    /* destination address = associated STA or BC/MC */
    if ((asocFlag == 1) || ((dst[0]&0x1) == 0x1))
    {
        /* Allocate frame */
        if ((txBuf = zfwBufAllocate(dev, ZM_RX_FRAME_SIZE))
                == NULL)
        {
            zm_msg0_rx(ZM_LV_1, "Alloc intra-bss buf Fail!");
            goto zlAllocError;
        }

        /* Copy frame */
        len = zfwBufGetSize(dev, buf);
        for (i=0; i<len; i+=2)
        {
            temp = zmw_rx_buf_readh(dev, buf, i);
            zmw_tx_buf_writeh(dev, txBuf, i, temp);
        }
        zfwBufSetSize(dev, txBuf, len);

#ifdef ZM_ENABLE_NATIVE_WIFI
        /* Tx-A2 = Rx-A1, Tx-A3 = Rx-A2, Tx-A1 = Rx-A3 */
        for (i=0; i<6; i+=2)
        {
            temp = zmw_rx_buf_readh(dev, buf, ZM_WLAN_HEADER_A1_OFFSET+i);
            zmw_tx_buf_writeh(dev, txBuf, ZM_WLAN_HEADER_A2_OFFSET+i, temp);
            temp = zmw_rx_buf_readh(dev, buf, ZM_WLAN_HEADER_A2_OFFSET+i);
            zmw_tx_buf_writeh(dev, txBuf, ZM_WLAN_HEADER_A3_OFFSET+i, temp);
            temp = zmw_rx_buf_readh(dev, buf, ZM_WLAN_HEADER_A3_OFFSET+i);
            zmw_tx_buf_writeh(dev, txBuf, ZM_WLAN_HEADER_A1_OFFSET+i, temp);
        }

        #endif

        /* Transmit frame */
        /* Return error if port is disabled */
        if ((err = zfTxPortControl(dev, txBuf, vap)) == ZM_PORT_DISABLED)
        {
            err = ZM_ERR_TX_PORT_DISABLED;
            goto zlTxError;
        }

#if 1
        /* AP : Buffer frame for power saving STA */
        if ((ret = zfApBufferPsFrame(dev, txBuf, vap)) == 0)
        {
            /* forward frame if not been buffered */
            #if 1
            /* Put to VTXQ[ac] */
            ret = zfPutVtxq(dev, txBuf);
            /* Push VTXQ[ac] */
            zfPushVtxq(dev);
            #else
            zfTxSendEth(dev, txBuf, vap, ZM_INTERNAL_ALLOC_BUF, 0);
            #endif

        }
#endif
    }
    return asocFlag;

zlTxError:
    zfwBufFree(dev, txBuf, 0);
zlAllocError:
    return asocFlag;
}