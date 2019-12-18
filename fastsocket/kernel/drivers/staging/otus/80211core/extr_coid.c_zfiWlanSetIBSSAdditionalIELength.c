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
typedef  int /*<<< orphan*/  u8_t ;
typedef  scalar_t__ u32_t ;
typedef  int /*<<< orphan*/  u16_t ;
struct TYPE_3__ {scalar_t__ ibssAdditionalIESize; int /*<<< orphan*/  ibssAdditionalIE; } ;
struct TYPE_4__ {TYPE_1__ sta; } ;

/* Variables and functions */
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zfMemoryCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfiWlanSetIBSSAdditionalIELength(zdev_t* dev, u32_t ibssAdditionalIESize, u8_t* ibssAdditionalIE)
{
	zmw_get_wlan_dev(dev);

	if ( ibssAdditionalIESize )
    {
	    wd->sta.ibssAdditionalIESize = ibssAdditionalIESize;
        zfMemoryCopy(wd->sta.ibssAdditionalIE, ibssAdditionalIE, (u16_t)ibssAdditionalIESize);
    }
    else
    	wd->sta.ibssAdditionalIESize = 0;
}