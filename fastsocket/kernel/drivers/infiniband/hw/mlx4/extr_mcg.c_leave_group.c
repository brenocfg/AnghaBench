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
typedef  int /*<<< orphan*/  u8 ;
struct mcast_group {TYPE_1__* func; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; int /*<<< orphan*/  join_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCAST_NOT_MEMBER ; 
 int /*<<< orphan*/  adjust_membership (struct mcast_group*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int leave_group(struct mcast_group *group, int slave, u8 leave_state)
{
	int ret = 0;

	adjust_membership(group, leave_state, -1);
	group->func[slave].join_state &= ~leave_state;
	if (!group->func[slave].join_state) {
		group->func[slave].state = MCAST_NOT_MEMBER;
		ret = 1;
	}
	return ret;
}