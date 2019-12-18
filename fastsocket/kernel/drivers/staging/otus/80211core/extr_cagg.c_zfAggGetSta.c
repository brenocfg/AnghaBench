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
typedef  scalar_t__ u16_t ;
struct TYPE_2__ {scalar_t__ wlanMode; } ;

/* Variables and functions */
 scalar_t__ ZM_MODE_AP ; 
 TYPE_1__* wd ; 
 scalar_t__ zfApFindSta (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 
 scalar_t__ zmw_rx_buf_readh (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

u16_t zfAggGetSta(zdev_t* dev, zbuf_t* buf)
{
    u16_t id;
    u16_t dst[3];

    zmw_get_wlan_dev(dev);

    zmw_declare_for_critical_section();

    dst[0] = zmw_rx_buf_readh(dev, buf, 0);
    dst[1] = zmw_rx_buf_readh(dev, buf, 2);
    dst[2] = zmw_rx_buf_readh(dev, buf, 4);

    zmw_enter_critical_section(dev);

    if(wd->wlanMode == ZM_MODE_AP) {
        id = zfApFindSta(dev, dst);
    }
    else {
        id = 0;
    }
    zmw_leave_critical_section(dev);

#if ZM_AGG_FPGA_DEBUG
    id = 0;
#endif

    return id;
}