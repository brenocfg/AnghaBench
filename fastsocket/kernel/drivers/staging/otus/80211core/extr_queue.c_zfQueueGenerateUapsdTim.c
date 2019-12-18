#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  zbuf_t ;
typedef  size_t u8_t ;
typedef  size_t u16_t ;
struct zsQueue {size_t head; size_t tail; size_t sizeMask; TYPE_1__* cell; } ;
struct TYPE_7__ {TYPE_2__* staTable; } ;
struct TYPE_8__ {TYPE_3__ ap; } ;
struct TYPE_6__ {scalar_t__ psMode; int qosInfo; } ;
struct TYPE_5__ {int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 TYPE_4__* wd ; 
 size_t zfApFindSta (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  zfQueueRemovewithIndex (int /*<<< orphan*/ *,struct zsQueue*,size_t,size_t*) ; 
 int /*<<< orphan*/  zfwBufFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t zmw_buf_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

void zfQueueGenerateUapsdTim(zdev_t* dev, struct zsQueue* q,
        u8_t* uniBitMap, u16_t* highestByte)
{
    zbuf_t* psBuf;
    u8_t dst[6];
    u16_t id, aid, index, i;
    u16_t bitPosition;
    u16_t bytePosition;
    zmw_get_wlan_dev(dev);
    zmw_declare_for_critical_section();

    zmw_enter_critical_section(dev);

    index = q->head;

    while (index != q->tail)
    {
        psBuf = q->cell[index].buf;
        for (i=0; i<6; i++)
        {
            dst[i] = zmw_buf_readb(dev, psBuf, i);
        }
        /* TODO : use u8_t* fot MAC address */
        if (((id = zfApFindSta(dev, (u16_t*)dst)) != 0xffff)
                && (wd->ap.staTable[id].psMode != 0))
        {
            /* Calculate PVB only when all AC are delivery-enabled */
            if ((wd->ap.staTable[id].qosInfo & 0xf) == 0xf)
            {
                aid = id + 1;
                bitPosition = (1 << (aid & 0x7));
                bytePosition = (aid >> 3);
                uniBitMap[bytePosition] |= bitPosition;

                if (bytePosition>*highestByte)
                {
                    *highestByte = bytePosition;
                }
            }
            index = (index+1) & q->sizeMask;
        }
        else
        {
            /* Free garbage UAPSD frame */
            zfQueueRemovewithIndex(dev, q, index, dst);
            zfwBufFree(dev, psBuf, 0);
        }
    }
    zmw_leave_critical_section(dev);

    return;
}