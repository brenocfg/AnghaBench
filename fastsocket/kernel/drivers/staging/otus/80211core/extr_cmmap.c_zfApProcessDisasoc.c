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
typedef  int /*<<< orphan*/  zbuf_t ;
typedef  int /*<<< orphan*/  u8_t ;
typedef  int u16_t ;
struct TYPE_5__ {TYPE_1__* staTable; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* zfcbDisAsocNotify ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ;TYPE_2__ ap; } ;
struct TYPE_4__ {scalar_t__ valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_3__* wd ; 
 int zfApFindSta (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

void zfApProcessDisasoc(zdev_t* dev, zbuf_t* buf, u16_t* src, u16_t apId)
{
    u16_t aid;
    zmw_get_wlan_dev(dev);
    zmw_declare_for_critical_section();

    zmw_enter_critical_section(dev);
    /* AP : if SA=associated STA then deauthenticate STA */
    if ((aid = zfApFindSta(dev, src)) != 0xffff)
    {
        /* Clear STA table */
        wd->ap.staTable[aid].valid = 0;
        zmw_leave_critical_section(dev);
        if (wd->zfcbDisAsocNotify != NULL)
        {
            wd->zfcbDisAsocNotify(dev, (u8_t*)src, apId);
        }
    }
    zmw_leave_critical_section(dev);

}