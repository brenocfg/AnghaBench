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
typedef  size_t u8_t ;
typedef  size_t u16_t ;
struct TYPE_5__ {int* timBcmcBit; scalar_t__* bcmcTail; scalar_t__* bcmcHead; size_t uniHead; size_t uniTail; int /*<<< orphan*/  uapsdQ; TYPE_1__* staTable; int /*<<< orphan*/ ** uniArray; } ;
struct TYPE_6__ {scalar_t__ CurrentDtimCount; scalar_t__ dtim; TYPE_2__ ap; } ;
struct TYPE_4__ {scalar_t__ psMode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_LV_0 ; 
 int /*<<< orphan*/  ZM_LV_3 ; 
 int ZM_UNI_ARRAY_SIZE ; 
 size_t ZM_WLAN_EID_TIM ; 
 TYPE_3__* wd ; 
 size_t zfApFindSta (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  zfApRemoveFromPsQueue (int /*<<< orphan*/ *,size_t,size_t*) ; 
 int /*<<< orphan*/  zfPushVtxq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfPutVtxq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfQueueGenerateUapsdTim (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*,size_t*) ; 
 int /*<<< orphan*/  zfwBufFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zm_assert (int) ; 
 int /*<<< orphan*/  zm_msg0_mm (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zm_msg1_mm (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 
 size_t zmw_tx_buf_readh (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zmw_tx_buf_writeb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,size_t) ; 

u16_t zfApAddIeTim(zdev_t* dev, zbuf_t* buf, u16_t offset, u16_t vap)
{
    u8_t uniBitMap[9];
    u16_t highestByte;
    u16_t i;
    u16_t lenOffset;
    u16_t id;
    u16_t dst[3];
    u16_t aid;
    u16_t bitPosition;
    u16_t bytePosition;
    zbuf_t* psBuf;
    zbuf_t* tmpBufArray[ZM_UNI_ARRAY_SIZE];
    u16_t tmpBufArraySize = 0;

    zmw_get_wlan_dev(dev);

    zmw_declare_for_critical_section();

    /* Element ID */
    zmw_tx_buf_writeb(dev, buf, offset++, ZM_WLAN_EID_TIM);

    /* offset of Element Length */
    lenOffset = offset++;

    /* Information : TIM */
    /* DTIM count */
    /* TODO : Doesn't work for Virtual AP's case */
    wd->CurrentDtimCount++;
    if (wd->CurrentDtimCount >= wd->dtim)
    {
        wd->CurrentDtimCount = 0;
    }
    zmw_tx_buf_writeb(dev, buf, offset++, wd->CurrentDtimCount);
    /* DTIM period */
    zmw_tx_buf_writeb(dev, buf, offset++, wd->dtim);
    /* bitmap offset */
    zmw_tx_buf_writeb(dev, buf, offset++, 0);

    /* Update BCMC bit */
    if (wd->CurrentDtimCount == 0)
    {
        zmw_enter_critical_section(dev);
        wd->ap.timBcmcBit[vap] = (wd->ap.bcmcTail[vap]!=wd->ap.bcmcHead[vap])?1:0;
        zmw_leave_critical_section(dev);
    }
    else
    {
        wd->ap.timBcmcBit[vap] = 0;
    }

    /* Update Unicast bitmap */
    /* reset bit map */
    for (i=0; i<9; i++)
    {
        uniBitMap[i] = 0;
    }
    highestByte = 0;
#if 1

    zmw_enter_critical_section(dev);

    id = wd->ap.uniHead;
    while (id != wd->ap.uniTail)
    {
        psBuf = wd->ap.uniArray[id];

        /* TODO : Aging PS frame after queuing for more than 10 seconds */

        /* get destination STA's aid */
        dst[0] = zmw_tx_buf_readh(dev, psBuf, 0);
        dst[1] = zmw_tx_buf_readh(dev, psBuf, 2);
        dst[2] = zmw_tx_buf_readh(dev, psBuf, 4);
        if ((aid = zfApFindSta(dev, dst)) != 0xffff)
        {
            if (wd->ap.staTable[aid].psMode != 0)
            {
                zm_msg1_mm(ZM_LV_0, "aid=",aid);
                aid++;
                zm_assert(aid<=64);
                bitPosition = (1 << (aid & 0x7));
                bytePosition = (aid >> 3);
                uniBitMap[bytePosition] |= bitPosition;

                if (bytePosition>highestByte)
                {
                    highestByte = bytePosition;
                }
                id = (id+1) & (ZM_UNI_ARRAY_SIZE-1);
            }
            else
            {
                zm_msg0_mm(ZM_LV_0, "Send PS frame which STA no longer in PS mode");
                /* Send PS frame which STA no longer in PS mode */
                zfApRemoveFromPsQueue(dev, id, dst);
                tmpBufArray[tmpBufArraySize++] = psBuf;
            }
        }
        else
        {
            zm_msg0_mm(ZM_LV_0, "Free garbage PS frame");
            /* Free garbage PS frame */
            zfApRemoveFromPsQueue(dev, id, dst);
            zfwBufFree(dev, psBuf, 0);
        }
    }

    zmw_leave_critical_section(dev);
#endif

    zfQueueGenerateUapsdTim(dev, wd->ap.uapsdQ, uniBitMap, &highestByte);

    zm_msg1_mm(ZM_LV_3, "bm=",uniBitMap[0]);
    zm_msg1_mm(ZM_LV_3, "highestByte=",highestByte);
    zm_msg1_mm(ZM_LV_3, "timBcmcBit[]=",wd->ap.timBcmcBit[vap]);

    /* bitmap */
    zmw_tx_buf_writeb(dev, buf, offset++,
                         uniBitMap[0] | wd->ap.timBcmcBit[vap]);
    for (i=0; i<highestByte; i++)
    {
        zmw_tx_buf_writeb(dev, buf, offset++, uniBitMap[i+1]);
    }

    /* Element Length */
    zmw_tx_buf_writeb(dev, buf, lenOffset, highestByte+4);

    for (i=0; i<tmpBufArraySize; i++)
    {
        /* Put to VTXQ[ac] */
        zfPutVtxq(dev, tmpBufArray[i]);
    }
    /* Push VTXQ[ac] */
    zfPushVtxq(dev);

    return offset;
}