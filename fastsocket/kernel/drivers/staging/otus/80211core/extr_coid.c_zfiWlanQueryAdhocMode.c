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
typedef  scalar_t__ u8_t ;
typedef  int /*<<< orphan*/  u32_t ;
struct TYPE_5__ {int /*<<< orphan*/  bIbssGMode; } ;
struct TYPE_4__ {int /*<<< orphan*/  adhocMode; } ;
struct TYPE_6__ {TYPE_2__ wfc; TYPE_1__ ws; } ;

/* Variables and functions */
 TYPE_3__* wd ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

u32_t zfiWlanQueryAdhocMode(zdev_t* dev, u8_t bWrapper)
{
    u32_t adhocMode;

    zmw_get_wlan_dev(dev);

    if ( bWrapper )
    {
        adhocMode = wd->ws.adhocMode;
    }
    else
    {
        adhocMode = wd->wfc.bIbssGMode;
    }

    return adhocMode;
}