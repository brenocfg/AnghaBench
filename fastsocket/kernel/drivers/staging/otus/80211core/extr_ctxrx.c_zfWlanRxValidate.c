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
typedef  int u8_t ;
typedef  int u16_t ;
struct TYPE_3__ {int enableDrvBA; } ;
struct TYPE_4__ {scalar_t__ wlanMode; TYPE_1__ sta; } ;

/* Variables and functions */
 int ZM_ERR_MAX_RX_FRAME_LENGTH ; 
 int ZM_ERR_MIN_RX_ENCRYPT_FRAME_LENGTH ; 
 int ZM_ERR_MIN_RX_FRAME_LENGTH ; 
 int ZM_ERR_RX_BAR_FRAME ; 
 int ZM_ERR_RX_FRAME_TYPE ; 
 scalar_t__ ZM_MODE_AP ; 
 scalar_t__ ZM_MODE_PSEUDO ; 
 int ZM_SUCCESS ; 
 int ZM_WLAN_FRAME_TYPE_BAR ; 
 int ZM_WLAN_MAX_RX_SIZE ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zfAggRecvBAR (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zfStaRxValidateFrame (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zfwBufGetSize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int zmw_rx_buf_readh (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

u16_t zfWlanRxValidate(zdev_t* dev, zbuf_t* buf)
{
    u16_t frameType;
    u16_t frameCtrl;
    u16_t frameLen;
    u16_t ret;
    u8_t  frameSubType;

    zmw_get_wlan_dev(dev);

    frameCtrl = zmw_rx_buf_readh(dev, buf, 0);
    frameType = frameCtrl & 0xC;
    frameSubType = (frameCtrl & 0xF0) >> 4;

    frameLen = zfwBufGetSize(dev, buf);

    /* Accept Data/Management frame with protocol version = 0 */
    if ((frameType == 0x8) || (frameType == 0x0))
    {

        /* TODO : check rx status => erro bit */

        /* Check Minimum Length with Wep */
        if ((frameCtrl & 0x4000) != 0)
        {
            /* Minimum Length =                                       */
            /*     PLCP(5)+Header(24)+IV(4)+ICV(4)+CRC(4)+RxStatus(8) */
            if (frameLen < 32)
            {
                return ZM_ERR_MIN_RX_ENCRYPT_FRAME_LENGTH;
            }
        }
        else if ( frameSubType == 0x5 || frameSubType == 0x8 )
        {
            /* Minimum Length = PLCP(5)+MACHeader(24)+Timestamp(8)+BeaconInterval(2)+Cap(2)+CRC(4)+RxStatus(8) */
            if (frameLen < 36)
            {
                return ZM_ERR_MIN_RX_FRAME_LENGTH;
            }
        }
        else
        {
            /* Minimum Length = PLCP(5)+MACHeader(24)+CRC(4)+RxStatus(8) */
            if (frameLen < 24)
            {
                return ZM_ERR_MIN_RX_FRAME_LENGTH;
            }
        }

        /* Check if frame Length > ZM_WLAN_MAX_RX_SIZE. */
        if (frameLen > ZM_WLAN_MAX_RX_SIZE)
        {
            return ZM_ERR_MAX_RX_FRAME_LENGTH;
        }
    }
    else if ((frameCtrl&0xff) == 0xa4)
    {
        /* PsPoll */
        //zm_msg0_rx(ZM_LV_0, "rx pspoll");
    }
    else if ((frameCtrl&0xff) == ZM_WLAN_FRAME_TYPE_BAR)
    {
        if (wd->sta.enableDrvBA == 1)
        {
            zfAggRecvBAR(dev, buf);
        }

        return ZM_ERR_RX_BAR_FRAME;
    }
    else
    {
        return ZM_ERR_RX_FRAME_TYPE;
    }

    if ( wd->wlanMode == ZM_MODE_AP )
    {
    }
    else if ( wd->wlanMode != ZM_MODE_PSEUDO )
    {
        if ( (ret=zfStaRxValidateFrame(dev, buf))!=ZM_SUCCESS )
        {
            //zm_debug_msg1("discard frame, code = ", ret);
            return ret;
        }
    }

    return ZM_SUCCESS;
}