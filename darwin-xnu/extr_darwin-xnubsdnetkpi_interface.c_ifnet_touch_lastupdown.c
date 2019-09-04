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
struct TYPE_3__ {int /*<<< orphan*/  if_lastupdown; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  TOUCHLASTCHANGE (int /*<<< orphan*/ *) ; 

errno_t
ifnet_touch_lastupdown(ifnet_t interface)
{
	if (interface == NULL) {
		return (EINVAL);
	}

	TOUCHLASTCHANGE(&interface->if_lastupdown);

	return (0);
}