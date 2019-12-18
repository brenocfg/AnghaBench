#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ifnet_t ;
typedef  int /*<<< orphan*/  errno_t ;
typedef  int boolean_t ;
struct TYPE_3__ {int if_xflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int IFXF_LOW_POWER ; 

errno_t
ifnet_get_low_power_mode(ifnet_t ifp, boolean_t *on)
{
	if (ifp == NULL || on == NULL)
		return (EINVAL);

	*on  = !!(ifp->if_xflags & IFXF_LOW_POWER);

	return (0);
}