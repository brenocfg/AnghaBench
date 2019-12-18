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
typedef  size_t u16_t ;
struct TYPE_4__ {TYPE_1__** aggQPool; } ;
struct TYPE_3__ {size_t ac; scalar_t__ clearFlag; scalar_t__ aggReady; scalar_t__ aggQEnabled; } ;

/* Variables and functions */
 size_t ZM_AGG_POOL_SIZE ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

u16_t zfAggTxReadyCount(zdev_t* dev, u16_t ac)
{
    u16_t i;
    u16_t readycount = 0;

    zmw_get_wlan_dev(dev);

    zmw_declare_for_critical_section();

    zmw_enter_critical_section(dev);

    for (i=0 ; i<ZM_AGG_POOL_SIZE; i++)
    {
        if (wd->aggQPool[i]->aggQEnabled && (wd->aggQPool[i]->aggReady || \
                wd->aggQPool[i]->clearFlag) && ac == wd->aggQPool[i]->ac)
            readycount++;
    }

    zmw_leave_critical_section(dev);

    return readycount;
}