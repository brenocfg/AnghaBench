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
typedef  int u8_t ;
typedef  int u16_t ;
struct TYPE_3__ {int protectedObss; } ;
struct TYPE_4__ {TYPE_1__ ap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_LV_3 ; 
 int /*<<< orphan*/  ZM_WLAN_EID_ERP ; 
 int ZM_WLAN_USE_PROTECTION_BIT ; 
 TYPE_2__* wd ; 
 int zfFindElement (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zm_msg0_mm (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int zmw_rx_buf_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void zfApProcessBeacon(zdev_t* dev, zbuf_t* buf)
{
    u16_t offset;
    u8_t ch;

    zmw_get_wlan_dev(dev);

    zm_msg0_mm(ZM_LV_3, "Rx beacon");

    /* update Non-ERP flag(wd->ap.nonErpObss) */
    if ((offset = zfFindElement(dev, buf, ZM_WLAN_EID_ERP)) == 0xffff)
    {
        /* 11b OBSS */
        wd->ap.protectedObss++;
        return;
    }

    ch = zmw_rx_buf_readb(dev, buf, offset+2);
    if ((ch & ZM_WLAN_USE_PROTECTION_BIT) == ZM_WLAN_USE_PROTECTION_BIT)
    {
        /* Protected OBSS */
        wd->ap.protectedObss = 1;
    }

    return;
}