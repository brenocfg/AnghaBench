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
struct zsMicVar {int /*<<< orphan*/  k1; int /*<<< orphan*/  k0; } ;
struct TYPE_3__ {scalar_t__ wmeConnected; } ;
struct TYPE_4__ {scalar_t__ wlanMode; TYPE_1__ sta; } ;

/* Variables and functions */
 int ZM_MIC_FAILURE ; 
 int ZM_MIC_SUCCESS ; 
 scalar_t__ ZM_MODE_AP ; 
 scalar_t__ ZM_MODE_INFRASTRUCTURE ; 
 int ZM_SIZE_OF_EXT_IV ; 
 int ZM_SIZE_OF_IV ; 
 int ZM_SIZE_OF_WLAN_DATA_HEADER ; 
 int /*<<< orphan*/  ZM_WLAN_HEADER_A1_OFFSET ; 
 int /*<<< orphan*/  ZM_WLAN_HEADER_A2_OFFSET ; 
 int /*<<< orphan*/  ZM_WLAN_HEADER_A3_OFFSET ; 
 TYPE_2__* wd ; 
 struct zsMicVar* zfApGetRxMicKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfCopyFromRxBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zfMicAppendByte (int,struct zsMicVar*) ; 
 int /*<<< orphan*/  zfMicClear (struct zsMicVar*) ; 
 int /*<<< orphan*/  zfMicGetMic (int*,struct zsMicVar*) ; 
 int /*<<< orphan*/  zfRxBufferEqualToStr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int,int) ; 
 struct zsMicVar* zfStaGetRxMicKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zfwBufGetSize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int zmw_rx_buf_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

u8_t zfMicRxVerify(zdev_t* dev, zbuf_t* buf)
{
    struct zsMicVar*  pMicKey;
    struct zsMicVar    MyMicKey;
    u8_t   mic[8];
    u8_t   da[6];
    u8_t   sa[6];
    u8_t   bValue;
    u16_t  i, payloadOffset, tailOffset;

    zmw_get_wlan_dev(dev);

    /* need not check MIC if pMicKEy is equal to NULL */
    if ( wd->wlanMode == ZM_MODE_AP )
    {
        pMicKey = zfApGetRxMicKey(dev, buf);

        if ( pMicKey != NULL )
        {
            zfCopyFromRxBuffer(dev, buf, sa, ZM_WLAN_HEADER_A2_OFFSET, 6);
            zfCopyFromRxBuffer(dev, buf, da, ZM_WLAN_HEADER_A3_OFFSET, 6);
        }
        else
        {
            return ZM_MIC_SUCCESS;
        }
    }
    else if ( wd->wlanMode == ZM_MODE_INFRASTRUCTURE )
    {
        pMicKey = zfStaGetRxMicKey(dev, buf);

        if ( pMicKey != NULL )
        {
            zfCopyFromRxBuffer(dev, buf, sa, ZM_WLAN_HEADER_A3_OFFSET, 6);
            zfCopyFromRxBuffer(dev, buf, da, ZM_WLAN_HEADER_A1_OFFSET, 6);
        }
        else
        {
            return ZM_MIC_SUCCESS;
        }
    }
    else
    {
        return ZM_MIC_SUCCESS;
    }

    MyMicKey.k0=pMicKey->k0;
    MyMicKey.k1=pMicKey->k1;
    pMicKey = &MyMicKey;

    zfMicClear(pMicKey);
    tailOffset = zfwBufGetSize(dev, buf);
    tailOffset -= 8;

    /* append DA */
    for(i=0; i<6; i++)
    {
        zfMicAppendByte(da[i], pMicKey);
    }
    /* append SA */
    for(i=0; i<6; i++)
    {
        zfMicAppendByte(sa[i], pMicKey);
    }

    /* append for alignment */
    if ((zmw_rx_buf_readb(dev, buf, 0) & 0x80) != 0)
        zfMicAppendByte(zmw_rx_buf_readb(dev, buf,24)&0x7, pMicKey);
    else
        zfMicAppendByte(0, pMicKey);
    zfMicAppendByte(0, pMicKey);
    zfMicAppendByte(0, pMicKey);
    zfMicAppendByte(0, pMicKey);

    /* append payload */
    payloadOffset = ZM_SIZE_OF_WLAN_DATA_HEADER +
                    ZM_SIZE_OF_IV +
                    ZM_SIZE_OF_EXT_IV;

    if ((zmw_rx_buf_readb(dev, buf, 0) & 0x80) != 0)
    {
        /* Qos Packet, Plcpheader + 2 */
        if (wd->wlanMode == ZM_MODE_AP)
        {
            /* TODO : Rx Qos element offset in software MIC check */
        }
        else if (wd->wlanMode == ZM_MODE_INFRASTRUCTURE)
        {
            if (wd->sta.wmeConnected != 0)
            {
                payloadOffset += 2;
            }
        }
    }

    for(i=payloadOffset; i<tailOffset; i++)
    {
        bValue = zmw_rx_buf_readb(dev, buf, i);
        zfMicAppendByte(bValue, pMicKey);
    }

    zfMicGetMic(mic, pMicKey);

    if ( !zfRxBufferEqualToStr(dev, buf, mic, tailOffset, 8) )
    {
        return ZM_MIC_FAILURE;
    }

    return ZM_MIC_SUCCESS;
}