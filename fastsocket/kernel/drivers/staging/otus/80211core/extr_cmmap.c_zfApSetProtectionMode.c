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
typedef  scalar_t__ u16_t ;
struct TYPE_3__ {scalar_t__ protectionMode; } ;
struct TYPE_4__ {TYPE_1__ ap; } ;

/* Variables and functions */
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfApSetProtectionMode(zdev_t* dev, u16_t mode)
{
    zmw_get_wlan_dev(dev);

    if (mode == 0)
    {
        if (wd->ap.protectionMode != mode)
        {
            /* Write MAC&PHY registers to disable protection */

            wd->ap.protectionMode = mode;
        }

    }
    else
    {
        if (wd->ap.protectionMode != mode)
        {
            /* Write MAC&PHY registers to enable protection */

            wd->ap.protectionMode = mode;
        }
    }
    return;
}