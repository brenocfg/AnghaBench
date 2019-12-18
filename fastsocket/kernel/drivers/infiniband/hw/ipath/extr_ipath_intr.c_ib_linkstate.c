#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct ipath_devdata {scalar_t__ ib_init; scalar_t__ ib_arm; scalar_t__ ib_active; } ;

/* Variables and functions */
 scalar_t__ ipath_ib_state (struct ipath_devdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *ib_linkstate(struct ipath_devdata *dd, u64 ibcs)
{
	char *ret;
	u32 state;

	state = ipath_ib_state(dd, ibcs);
	if (state == dd->ib_init)
		ret = "Init";
	else if (state == dd->ib_arm)
		ret = "Arm";
	else if (state == dd->ib_active)
		ret = "Active";
	else
		ret = "Down";
	return ret;
}