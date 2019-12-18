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
typedef  scalar_t__ u8_t ;
struct zsHpPriv {int slotType; } ;
struct TYPE_2__ {struct zsHpPriv* hpPrivate; } ;

/* Variables and functions */
 TYPE_1__* wd ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfHpSetSlotTime(zdev_t* dev, u8_t type)
{
    struct zsHpPriv* hpPriv;

    zmw_get_wlan_dev(dev);
    hpPriv = wd->hpPrivate;

    if (type == 0)
    {
        //normal slot = 20us
        hpPriv->slotType = 0;
    }
    else //if (type == 1)
    {
        //short slot = 9us
        hpPriv->slotType = 1;
    }

    return;
}