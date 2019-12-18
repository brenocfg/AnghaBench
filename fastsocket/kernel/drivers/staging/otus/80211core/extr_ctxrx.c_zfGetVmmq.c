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
struct TYPE_2__ {size_t vmmqHead; size_t vmmqTail; int /*<<< orphan*/ ** vmmq; } ;

/* Variables and functions */
 int ZM_VMMQ_SIZE_MASK ; 
 TYPE_1__* wd ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

zbuf_t* zfGetVmmq(zdev_t* dev)
{
    zbuf_t* buf;
    zmw_get_wlan_dev(dev);
    zmw_declare_for_critical_section();

    zmw_enter_critical_section(dev);
    if (wd->vmmqHead != wd->vmmqTail)
    {
        buf = wd->vmmq[wd->vmmqTail];
        wd->vmmqTail = ((wd->vmmqTail + 1) & ZM_VMMQ_SIZE_MASK);
        zmw_leave_critical_section(dev);
        return buf;
    }
    else
    {
        zmw_leave_critical_section(dev);
        return 0; //VTXQ[] empty
    }
}