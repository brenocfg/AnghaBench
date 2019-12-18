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
typedef  size_t u16_t ;
struct TYPE_3__ {size_t uniHead; size_t uniTail; size_t* bcmcHead; size_t* bcmcTail; int /*<<< orphan*/ *** bcmcArray; int /*<<< orphan*/ ** uniArray; } ;
struct TYPE_4__ {TYPE_1__ ap; } ;

/* Variables and functions */
 int ZM_BCMC_ARRAY_SIZE ; 
 int /*<<< orphan*/  ZM_ERR_FLUSH_PS_QUEUE ; 
 size_t ZM_MAX_AP_SUPPORT ; 
 int ZM_UNI_ARRAY_SIZE ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zfwBufFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zm_assert (int) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

void zfApFlushBufferedPsFrame(zdev_t* dev)
{
    u16_t emptyFlag;
    u16_t freeCount;
    u16_t vap;
    zbuf_t* psBuf = NULL;
    zmw_get_wlan_dev(dev);
    zmw_declare_for_critical_section();

    freeCount = 0;
    emptyFlag = 0;
    while (1)
    {
        psBuf = NULL;
        zmw_enter_critical_section(dev);
        if (wd->ap.uniHead != wd->ap.uniTail)
        {
            psBuf = wd->ap.uniArray[wd->ap.uniHead];
            wd->ap.uniHead = (wd->ap.uniHead + 1) & (ZM_UNI_ARRAY_SIZE - 1);
        }
        else
        {
            emptyFlag = 1;
        }
        zmw_leave_critical_section(dev);

        if (psBuf != NULL)
        {
            zfwBufFree(dev, psBuf, ZM_ERR_FLUSH_PS_QUEUE);
        }
        zm_assert(freeCount++ < (ZM_UNI_ARRAY_SIZE*2));

        if (emptyFlag != 0)
        {
            break;
        }
    }

    for (vap=0; vap<ZM_MAX_AP_SUPPORT; vap++)
    {
        freeCount = 0;
        emptyFlag = 0;
        while (1)
        {
            psBuf = NULL;
            zmw_enter_critical_section(dev);
            if (wd->ap.bcmcHead[vap] != wd->ap.bcmcTail[vap])
            {
                psBuf = wd->ap.bcmcArray[vap][wd->ap.bcmcHead[vap]];
                wd->ap.bcmcHead[vap] = (wd->ap.bcmcHead[vap] + 1)
                        & (ZM_BCMC_ARRAY_SIZE - 1);
            }
            else
            {
                emptyFlag = 1;
            }
            zmw_leave_critical_section(dev);

            if (psBuf != NULL)
            {
                zfwBufFree(dev, psBuf, ZM_ERR_FLUSH_PS_QUEUE);
            }
            zm_assert(freeCount++ < (ZM_BCMC_ARRAY_SIZE*2));

            if (emptyFlag != 0)
            {
                break;
            }
        }
    }
    return;
}