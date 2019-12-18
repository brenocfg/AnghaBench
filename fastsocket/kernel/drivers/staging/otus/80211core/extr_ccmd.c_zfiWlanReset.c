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
typedef  int /*<<< orphan*/  u16_t ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_WLAN_STATE_DISABLED ; 
 TYPE_1__* wd ; 
 int /*<<< orphan*/  zfWlanReset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

u16_t zfiWlanReset(zdev_t *dev)
{
	zmw_get_wlan_dev(dev);

	wd->state = ZM_WLAN_STATE_DISABLED;

	return zfWlanReset(dev);
}