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
typedef  size_t u16_t ;
struct TYPE_3__ {size_t uniHead; size_t uniTail; int /*<<< orphan*/ ** uniArray; } ;
struct TYPE_4__ {TYPE_1__ ap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_EXTERNAL_ALLOC_BUF ; 
 int ZM_UNI_ARRAY_SIZE ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zfApRemoveFromPsQueue (int /*<<< orphan*/ *,size_t,size_t*) ; 
 int /*<<< orphan*/  zfTxSendEth (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 
 size_t zmw_tx_buf_readh (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void zfApProcessPsPoll(zdev_t* dev, zbuf_t* buf)
{
    u16_t src[3];
    u16_t dst[3];
    zbuf_t* psBuf = NULL;
    u16_t id;
    u8_t moreData = 0;

    zmw_get_wlan_dev(dev);

    zmw_declare_for_critical_section();

    src[0] = zmw_tx_buf_readh(dev, buf, 10);
    src[1] = zmw_tx_buf_readh(dev, buf, 12);
    src[2] = zmw_tx_buf_readh(dev, buf, 14);

    /* Find ps buffer for PsPoll */
    zmw_enter_critical_section(dev);
    id = wd->ap.uniHead;
    while (id != wd->ap.uniTail)
    {
        psBuf = wd->ap.uniArray[id];

        dst[0] = zmw_tx_buf_readh(dev, psBuf, 0);
        dst[1] = zmw_tx_buf_readh(dev, psBuf, 2);
        dst[2] = zmw_tx_buf_readh(dev, psBuf, 4);

        if ((src[0] == dst[0]) && (src[1] == dst[1]) && (src[2] == dst[2]))
        {
            moreData = zfApRemoveFromPsQueue(dev, id, src);
            break;
        }
        else
        {
            psBuf = NULL;
        }
        id = (id + 1) & (ZM_UNI_ARRAY_SIZE - 1);
    }
    zmw_leave_critical_section(dev);

    /* Send ps buffer */
    if (psBuf != NULL)
    {
        /* Send with more data bit */
        zfTxSendEth(dev, psBuf, 0, ZM_EXTERNAL_ALLOC_BUF, moreData);
    }

    return;
}