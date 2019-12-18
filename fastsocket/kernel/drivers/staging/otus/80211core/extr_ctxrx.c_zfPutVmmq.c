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
typedef  int /*<<< orphan*/  u16_t ;
struct TYPE_2__ {int vmmqHead; int vmmqTail; int /*<<< orphan*/ ** vmmq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_ERR_VMMQ_FULL ; 
 int /*<<< orphan*/  ZM_LV_0 ; 
 int /*<<< orphan*/  ZM_SUCCESS ; 
 int ZM_VMMQ_SIZE_MASK ; 
 TYPE_1__* wd ; 
 int /*<<< orphan*/  zfwBufFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zm_msg0_mm (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

u16_t zfPutVmmq(zdev_t* dev, zbuf_t* buf)
{
    zmw_get_wlan_dev(dev);
    zmw_declare_for_critical_section();

    zmw_enter_critical_section(dev);
    if (((wd->vmmqHead + 1) & ZM_VMMQ_SIZE_MASK) != wd->vmmqTail)
    {
        wd->vmmq[wd->vmmqHead] = buf;
        wd->vmmqHead = ((wd->vmmqHead + 1) & ZM_VMMQ_SIZE_MASK);
        zmw_leave_critical_section(dev);
        return ZM_SUCCESS;
    }
    else
    {
        zmw_leave_critical_section(dev);

        zfwBufFree(dev, buf, ZM_SUCCESS);
        zm_msg0_mm(ZM_LV_0, "Packet discarded, VMmQ full");
        return ZM_ERR_VMMQ_FULL; //VTXQ[] Full
    }
}