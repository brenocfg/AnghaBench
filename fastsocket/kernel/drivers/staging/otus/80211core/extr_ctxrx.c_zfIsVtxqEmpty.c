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
typedef  int u8_t ;
struct TYPE_2__ {scalar_t__ vmmqHead; scalar_t__ vmmqTail; scalar_t__* vtxqHead; scalar_t__* vtxqTail; } ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 TYPE_1__* wd ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

u8_t zfIsVtxqEmpty(zdev_t* dev)
{
    u8_t isEmpty = TRUE;
    u8_t i;

    zmw_get_wlan_dev(dev);

    zmw_declare_for_critical_section();

    zmw_enter_critical_section(dev);

    if (wd->vmmqHead != wd->vmmqTail)
    {
        isEmpty = FALSE;
        goto check_done;
    }

    for(i=0; i < 4; i++)
    {
        if (wd->vtxqHead[i] != wd->vtxqTail[i])
        {
            isEmpty = FALSE;
            goto check_done;
        }
    }

check_done:
    zmw_leave_critical_section(dev);
    return isEmpty;
}