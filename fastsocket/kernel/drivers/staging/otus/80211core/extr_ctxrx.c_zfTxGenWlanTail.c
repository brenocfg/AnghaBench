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
struct zsMicVar {int dummy; } ;
struct TYPE_3__ {scalar_t__ wmeConnected; } ;
struct TYPE_4__ {scalar_t__ wlanMode; TYPE_1__ sta; } ;

/* Variables and functions */
 int ZM_80211_FRAME_IP_OFFSET ; 
 int ZM_80211_FRAME_TYPE_OFFSET ; 
 scalar_t__ ZM_MODE_AP ; 
 scalar_t__ ZM_MODE_INFRASTRUCTURE ; 
 int ZM_SIZE_OF_MIC ; 
 TYPE_2__* wd ; 
 struct zsMicVar* zfApGetTxMicKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  zfMicAppendByte (int,struct zsMicVar*) ; 
 int /*<<< orphan*/  zfMicClear (struct zsMicVar*) ; 
 int /*<<< orphan*/  zfMicGetMic (int*,struct zsMicVar*) ; 
 struct zsMicVar* zfStaGetTxMicKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zfwBufGetSize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int zmw_tx_buf_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

u16_t zfTxGenWlanTail(zdev_t* dev, zbuf_t* buf, u16_t* snap, u16_t snaplen,
                      u16_t* mic)
{
    struct zsMicVar*  pMicKey;
    u16_t  i, length, payloadOffset;
    u8_t   bValue, qosType = 0;
    u8_t   snapByte[12];

    zmw_get_wlan_dev(dev);

    if ( wd->wlanMode == ZM_MODE_AP )
    {
        pMicKey = zfApGetTxMicKey(dev, buf, &qosType);

        if ( pMicKey == NULL )
        {
            return 0;
        }
    }
    else if ( wd->wlanMode == ZM_MODE_INFRASTRUCTURE )
    {
        pMicKey = zfStaGetTxMicKey(dev, buf);

        if ( pMicKey == NULL )
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }

    length = zfwBufGetSize(dev, buf);

    zfMicClear(pMicKey);

    /* append DA and SA */
#ifdef ZM_ENABLE_NATIVE_WIFI
    for(i=16; i<22; i++)
    { // VISTA DA
        bValue = zmw_tx_buf_readb(dev, buf, i);
        zfMicAppendByte(bValue, pMicKey);
    }
    for(i=10; i<16; i++)
    { // VISTA SA
        bValue = zmw_tx_buf_readb(dev, buf, i);
        zfMicAppendByte(bValue, pMicKey);
    }
#else
    for(i=0; i<12; i++)
    {
        bValue = zmw_tx_buf_readb(dev, buf, i);
        zfMicAppendByte(bValue, pMicKey);
    }
#endif

    /* append for alignment */
    if ( wd->wlanMode == ZM_MODE_INFRASTRUCTURE )
    {
        if (wd->sta.wmeConnected != 0)
            zfMicAppendByte(zmw_tx_buf_readb(dev, buf, ZM_80211_FRAME_IP_OFFSET + 1) >> 5, pMicKey);
        else
            zfMicAppendByte(0, pMicKey);
    }
    else if ( wd->wlanMode == ZM_MODE_AP )
    {
        if (qosType == 1)
            zfMicAppendByte(zmw_tx_buf_readb(dev, buf, ZM_80211_FRAME_IP_OFFSET + 1) >> 5, pMicKey);
        else
            zfMicAppendByte(0, pMicKey);
    }
    else
    {
        /* TODO : Qos Software MIC in IBSS Mode */
        zfMicAppendByte(0, pMicKey);
    }
    zfMicAppendByte(0, pMicKey);
    zfMicAppendByte(0, pMicKey);
    zfMicAppendByte(0, pMicKey);

    if ( snaplen == 0 )
    {
        payloadOffset = ZM_80211_FRAME_IP_OFFSET;
    }
    else
    {
        payloadOffset = ZM_80211_FRAME_TYPE_OFFSET;

        for(i=0; i<(snaplen>>1); i++)
        {
            snapByte[i*2] = (u8_t) (snap[i] & 0xff);
            snapByte[i*2+1] = (u8_t) ((snap[i] >> 8) & 0xff);
        }

        for(i=0; i<snaplen; i++)
        {
            zfMicAppendByte(snapByte[i], pMicKey);
        }
    }

    for(i=payloadOffset; i<length; i++)
    {
        bValue = zmw_tx_buf_readb(dev, buf, i);
        zfMicAppendByte(bValue, pMicKey);
    }

    zfMicGetMic( (u8_t*) mic, pMicKey);

    return ZM_SIZE_OF_MIC;
}