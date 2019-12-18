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
typedef  int u8 ;
struct mcast_group {TYPE_1__* func; } ;
struct TYPE_2__ {int join_state; scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ MCAST_MEMBER ; 
 int /*<<< orphan*/  adjust_membership (struct mcast_group*,int,int) ; 

__attribute__((used)) static int join_group(struct mcast_group *group, int slave, u8 join_mask)
{
	int ret = 0;
	u8 join_state;

	/* remove bits that slave is already member of, and adjust */
	join_state = join_mask & (~group->func[slave].join_state);
	adjust_membership(group, join_state, 1);
	group->func[slave].join_state |= join_state;
	if (group->func[slave].state != MCAST_MEMBER && join_state) {
		group->func[slave].state = MCAST_MEMBER;
		ret = 1;
	}
	return ret;
}