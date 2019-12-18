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
typedef  int u8_t ;
typedef  int u32_t ;
typedef  int u16_t ;
typedef  scalar_t__ s16_t ;
struct TYPE_2__ {int /*<<< orphan*/  enableHALDbgInfo; } ;

/* Variables and functions */
 TYPE_1__* wd ; 
 int zfcConvertRateOFDM (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int zmw_rx_buf_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

u16_t zfHpGetPayloadLen(zdev_t* dev,
                        zbuf_t* buf,
                        u16_t len,
                        u16_t plcpHdrLen,
                        u32_t *rxMT,
                        u32_t *rxMCS,
                        u32_t *rxBW,
                        u32_t *rxSG
                        )
{
    u8_t modulation,mpduInd;
    u16_t low, high, msb;
    s16_t payloadLen = 0;

    zmw_get_wlan_dev(dev);

    mpduInd = zmw_rx_buf_readb(dev, buf, len-1);
    modulation = zmw_rx_buf_readb(dev, buf, (len-1)) & 0x3;
    *rxMT = modulation;

    //zm_debug_msg1(" modulation= ", modulation);
    switch (modulation) {
    case 0: /* CCK Mode */
        low = zmw_rx_buf_readb(dev, buf, 2);
        high = zmw_rx_buf_readb(dev, buf, 3);
        payloadLen = (low | high << 8) - 4;
        if (wd->enableHALDbgInfo)
        {
            *rxMCS = zmw_rx_buf_readb(dev, buf, 0);
            *rxBW  = 0;
            *rxSG  = 0;
        }
        break;
    case 1: /* Legacy-OFDM mode */
        low = zmw_rx_buf_readb(dev, buf, 0) >> 5;
        high = zmw_rx_buf_readb(dev, buf, 1);
        msb = zmw_rx_buf_readb(dev, buf, 2) & 0x1;
        payloadLen = (low | (high << 3) | (msb << 11)) - 4;
        if (wd->enableHALDbgInfo)
        {
            *rxMCS = zfcConvertRateOFDM(dev, buf);
            *rxBW  = 0;
            *rxSG  = 0;
        }
        break;
    case 2: /* HT OFDM mode */
        //zm_debug_msg1("aggregation= ", (zmw_rx_buf_readb(dev, buf, 6) >> 3) &0x1 );
        if ((mpduInd & 0x30) == 0x00 || (mpduInd & 0x30) == 0x10)    //single or last mpdu
            payloadLen = len - 24 - 4 - plcpHdrLen;  // - rxStatus - fcs
        else {
            payloadLen = len - 4 - 4 - plcpHdrLen;  // - rxStatus - fcs
            //zm_debug_msg1("first or middle mpdu, plcpHdrLen= ", plcpHdrLen);
        }
        if (wd->enableHALDbgInfo)
        {
            *rxMCS = zmw_rx_buf_readb(dev, buf, 3) & 0x7f;
            *rxBW  = (zmw_rx_buf_readb(dev, buf, 3) >> 7) & 0x1;
            *rxSG  = (zmw_rx_buf_readb(dev, buf, 6) >> 7) & 0x1;
        }
        break;
    default:
        break;

    }
    /* return the payload length - FCS */
    if (payloadLen < 0) payloadLen = 0;
    return payloadLen;
}