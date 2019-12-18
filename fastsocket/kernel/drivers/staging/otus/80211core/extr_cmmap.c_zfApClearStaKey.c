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
typedef  int /*<<< orphan*/  u8_t ;
typedef  int u16_t ;
typedef  int /*<<< orphan*/  bcAddr ;
struct TYPE_4__ {TYPE_2__* staTable; } ;
struct TYPE_6__ {TYPE_1__ ap; } ;
struct TYPE_5__ {int /*<<< orphan*/  encryMode; } ;

/* Variables and functions */
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ZM_LV_3 ; 
 int /*<<< orphan*/  ZM_NO_WEP ; 
 TYPE_3__* wd ; 
 int zfApFindSta (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  zfHpRemoveKey (int /*<<< orphan*/ *,int) ; 
 scalar_t__ zfMemoryIsEqual (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zm_msg0_mm (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

void zfApClearStaKey(zdev_t* dev, u16_t* addr)
{
    //struct zsWlanDev* wd = (struct zsWlanDev*) zmw_wlan_dev(dev);
    u16_t bcAddr[3] = { 0xffff, 0xffff, 0xffff };
    u16_t id;

    zmw_get_wlan_dev(dev);

    if (zfMemoryIsEqual((u8_t*)bcAddr, (u8_t*)addr, sizeof(bcAddr)) == TRUE)
    {
        /* Turn off group key information */
    //    zfClearKey(dev, 0);
    }
    else
    {
        zmw_declare_for_critical_section();

        zmw_enter_critical_section(dev);

        if ((id = zfApFindSta(dev, addr)) != 0xffff)
        {
            /* Turn off STA's key information */
            zfHpRemoveKey(dev, id+1);

            /* Update STA's Encryption Type */
            wd->ap.staTable[id].encryMode = ZM_NO_WEP;
        }
        else
        {
            zm_msg0_mm(ZM_LV_3, "Can't find STA address\n");
        }
        zmw_leave_critical_section(dev);
    }
}