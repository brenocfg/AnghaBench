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
struct TYPE_2__ {scalar_t__ aniEnable; } ;

/* Variables and functions */
 TYPE_1__* wd ; 
 int /*<<< orphan*/  zfHpAniAttach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

u8_t zfiWlanSetAniMode(zdev_t* dev, u8_t mode)
{
    zmw_get_wlan_dev(dev);

    wd->aniEnable = mode;
    if (mode)
        zfHpAniAttach(dev);

    return 0;
}