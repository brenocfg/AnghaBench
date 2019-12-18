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
typedef  size_t u16_t ;
struct TYPE_5__ {TYPE_1__* defragEntry; } ;
struct TYPE_6__ {int tick; TYPE_2__ defragTable; } ;
struct TYPE_4__ {scalar_t__ fragCount; int tick; int /*<<< orphan*/ * fragment; } ;

/* Variables and functions */
 int ZM_DEFRAG_AGING_TIME_SEC ; 
 int /*<<< orphan*/  ZM_LV_2 ; 
 size_t ZM_MAX_DEFRAG_ENTRIES ; 
 int ZM_TICK_PER_SECOND ; 
 TYPE_3__* wd ; 
 int /*<<< orphan*/  zfwBufFree (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zm_msg1_rx (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

void zfAgingDefragList(zdev_t* dev, u16_t flushFlag)
{
    u16_t i, j;
    zmw_get_wlan_dev(dev);
    zmw_declare_for_critical_section();

    zmw_enter_critical_section(dev);

    for(i=0; i<ZM_MAX_DEFRAG_ENTRIES; i++)
    {
        if (wd->defragTable.defragEntry[i].fragCount != 0 )
        {
            if (((wd->tick - wd->defragTable.defragEntry[i].tick) >
                        (ZM_DEFRAG_AGING_TIME_SEC * ZM_TICK_PER_SECOND))
               || (flushFlag != 0))
            {
                zm_msg1_rx(ZM_LV_2, "Aging defrag list :", i);
                /* Free the buffers in the defrag list */
                for (j=0; j<wd->defragTable.defragEntry[i].fragCount; j++)
                {
                    zfwBufFree(dev, wd->defragTable.defragEntry[i].fragment[j], 0);
                }
            }
        }
        wd->defragTable.defragEntry[i].fragCount = 0;
    }

    zmw_leave_critical_section(dev);

    return;
}