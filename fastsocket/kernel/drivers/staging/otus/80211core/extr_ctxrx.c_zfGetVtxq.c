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
struct TYPE_2__ {size_t* vtxqHead; size_t* vtxqTail; int /*<<< orphan*/ *** vtxq; } ;

/* Variables and functions */
 int ZM_VTXQ_SIZE_MASK ; 
 TYPE_1__* wd ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

zbuf_t* zfGetVtxq(zdev_t* dev, u8_t ac)
{
    zbuf_t* buf;

    zmw_get_wlan_dev(dev);

    zmw_declare_for_critical_section();

    ac &= 0x3;
    zmw_enter_critical_section(dev);
    if (wd->vtxqHead[ac] != wd->vtxqTail[ac])
    {
        buf = wd->vtxq[ac][wd->vtxqTail[ac]];
        wd->vtxqTail[ac] = ((wd->vtxqTail[ac] + 1) & ZM_VTXQ_SIZE_MASK);
        zmw_leave_critical_section(dev);
        return buf;
    }
    else
    {
        zmw_leave_critical_section(dev);
        return 0; //VTXQ[] empty
    }
}