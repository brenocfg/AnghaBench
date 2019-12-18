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
typedef  size_t u8_t ;
struct zsBssInfo {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ ** bssInfoArray; } ;
struct TYPE_4__ {TYPE_1__ sta; } ;

/* Variables and functions */
 size_t ZM_MAX_BSS ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zfBssInfoRefresh (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zfwMemFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zm_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfBssInfoDestroy(zdev_t* dev)
{
    u8_t   i;
    zmw_get_wlan_dev(dev);

    zfBssInfoRefresh(dev, 1);

    for( i=0; i< ZM_MAX_BSS; i++ )
    {
        if (wd->sta.bssInfoArray[i] != NULL)
        {
            zfwMemFree(dev, wd->sta.bssInfoArray[i], sizeof(struct zsBssInfo));
        }
        else
        {
            zm_assert(0);
        }
    }
    return;
}