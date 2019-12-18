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
struct TYPE_2__ {int /*<<< orphan*/  halState; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_HAL_STATE_INIT ; 
 TYPE_1__* wd ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

u16_t zfiWlanSuspend(zdev_t *dev)
{
	zmw_get_wlan_dev(dev);
	zmw_declare_for_critical_section();

	/* Change the HAL state to init so that any packet
	can't be transmitted between resume & HAL reinit.
	This would cause the chip hang issue in OTUS.
	*/
	zmw_enter_critical_section(dev);
	wd->halState = ZM_HAL_STATE_INIT;
	zmw_leave_critical_section(dev);

	return 0;
}