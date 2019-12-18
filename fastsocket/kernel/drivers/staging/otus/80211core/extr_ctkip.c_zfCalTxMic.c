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
typedef  int u16_t ;
struct zsMicVar {int dummy; } ;
struct TYPE_2__ {scalar_t__ wlanMode; } ;

/* Variables and functions */
 scalar_t__ ZM_MODE_AP ; 
 scalar_t__ ZM_MODE_INFRASTRUCTURE ; 
 TYPE_1__* wd ; 
 struct zsMicVar* zfApGetTxMicKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  zfMicAppendByte (int,struct zsMicVar*) ; 
 int /*<<< orphan*/  zfMicClear (struct zsMicVar*) ; 
 int /*<<< orphan*/  zfMicGetMic (int*,struct zsMicVar*) ; 
 struct zsMicVar* zfStaGetTxMicKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zfwBufGetSize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zm_debug_msg0 (char*) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int zmw_tx_buf_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void zfCalTxMic(zdev_t *dev, zbuf_t *buf, u8_t *snap, u16_t snapLen, u16_t offset, u16_t *da, u16_t *sa, u8_t up, u8_t *mic)
{
    struct zsMicVar*  pMicKey;
    u16_t  i;
    u16_t len;
    u8_t bValue;
    u8_t qosType;
    u8_t *pDa = (u8_t *)da;
    u8_t *pSa = (u8_t *)sa;

    zmw_get_wlan_dev(dev);

    /* need not check MIC if pMicKEy is equal to NULL */
    if ( wd->wlanMode == ZM_MODE_AP )
    {
        pMicKey = zfApGetTxMicKey(dev, buf, &qosType);

        if ( pMicKey == NULL )
            return;
    }
    else if ( wd->wlanMode == ZM_MODE_INFRASTRUCTURE )
    {
        pMicKey = zfStaGetTxMicKey(dev, buf);

        if ( pMicKey == NULL )
        {
            zm_debug_msg0("pMicKey is NULL");
            return;
        }
    }
    else
    {
        return;
    }

    zfMicClear(pMicKey);
    len = zfwBufGetSize(dev, buf);

    /* append DA */
    for(i = 0; i < 6; i++)
    {
        zfMicAppendByte(pDa[i], pMicKey);
    }

    /* append SA */
    for(i = 0; i < 6; i++)
    {
        zfMicAppendByte(pSa[i], pMicKey);
    }

    if (up != 0)
        zfMicAppendByte((up&0x7), pMicKey);
    else
        zfMicAppendByte(0, pMicKey);

    zfMicAppendByte(0, pMicKey);
    zfMicAppendByte(0, pMicKey);
    zfMicAppendByte(0, pMicKey);

    /* For Snap header */
    for(i = 0; i < snapLen; i++)
    {
        zfMicAppendByte(snap[i], pMicKey);
    }

    for(i = offset; i < len; i++)
    {
        bValue = zmw_tx_buf_readb(dev, buf, i);
        zfMicAppendByte(bValue, pMicKey);
    }

    zfMicGetMic(mic, pMicKey);
}