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
struct TYPE_2__ {scalar_t__ user_ref; } ;

/* Variables and functions */
 TYPE_1__ mng ; 
 int /*<<< orphan*/  tipc_detach (scalar_t__) ; 

void tipc_cfg_stop(void)
{
	if (mng.user_ref) {
		tipc_detach(mng.user_ref);
		mng.user_ref = 0;
	}
}