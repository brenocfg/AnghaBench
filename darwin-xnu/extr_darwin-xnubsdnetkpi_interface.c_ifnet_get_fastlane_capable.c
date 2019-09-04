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
struct TYPE_3__ {int if_eflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int IFEF_QOSMARKING_CAPABLE ; 

errno_t
ifnet_get_fastlane_capable(ifnet_t interface, boolean_t *capable)
{
	if (interface == NULL || capable == NULL)
		return (EINVAL);
	if (interface->if_eflags & IFEF_QOSMARKING_CAPABLE)
		*capable = true;
	else
		*capable = false;
	return (0);
}