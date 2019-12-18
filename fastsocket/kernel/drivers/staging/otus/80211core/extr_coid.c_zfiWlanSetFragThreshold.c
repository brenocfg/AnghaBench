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
typedef  int u16_t ;
struct TYPE_2__ {int fragThreshold; } ;

/* Variables and functions */
 TYPE_1__* wd ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

void zfiWlanSetFragThreshold(zdev_t* dev, u16_t fragThreshold)
{
    zmw_get_wlan_dev(dev);

    zmw_declare_for_critical_section();

    zmw_enter_critical_section(dev);

    if (fragThreshold == 0)
    {   /* fragmentation is disabled */
        wd->fragThreshold = 32767;
    }
    else if (fragThreshold < 256)
    {
        /* Minimum fragment threshold */
        wd->fragThreshold = 256;
    }
    else if (fragThreshold > 2346)
    {
        wd->fragThreshold = 2346;
    }
    else
    {
        wd->fragThreshold = fragThreshold & 0xfffe;
    }

    zmw_leave_critical_section(dev);
}