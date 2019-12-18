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
typedef  size_t u16_t ;
struct TYPE_2__ {int /*<<< orphan*/ * vtxqTail; int /*<<< orphan*/ * vtxqHead; } ;

/* Variables and functions */
 TYPE_1__* wd ; 
 size_t zm_agg_qlen (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t zm_agg_weight (size_t) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

u16_t zfAggTxPartial(zdev_t* dev, u16_t ac, u16_t readycount)
{
    u16_t qlen;
    u16_t partial;

    zmw_get_wlan_dev(dev);

    zmw_declare_for_critical_section();

    zmw_enter_critical_section(dev);

    qlen = zm_agg_qlen(dev, wd->vtxqHead[ac], wd->vtxqTail[ac]);

    if ((qlen + readycount) > 0)
    {
        partial = (u16_t)( zm_agg_weight(ac) * ((u16_t)qlen/(qlen + \
                        readycount)) );
    }
    else
    {
        partial = 0;
    }

    zmw_leave_critical_section(dev);

    if (partial > qlen)
        partial = qlen;

    return partial;
}