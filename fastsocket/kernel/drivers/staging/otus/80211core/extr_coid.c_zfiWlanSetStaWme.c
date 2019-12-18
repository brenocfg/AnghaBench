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
typedef  int u8_t ;
struct TYPE_3__ {int staWmeEnabled; int staWmeQosInfo; } ;
struct TYPE_4__ {TYPE_1__ ws; } ;

/* Variables and functions */
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfiWlanSetStaWme(zdev_t* dev, u8_t enable, u8_t uapsdInfo)
{
    zmw_get_wlan_dev(dev);

    wd->ws.staWmeEnabled = enable & 0x3;
    if ((enable & 0x2) != 0)
    {
        wd->ws.staWmeQosInfo = uapsdInfo & 0x6f;
    }
    else
    {
        wd->ws.staWmeQosInfo = 0;
    }
}