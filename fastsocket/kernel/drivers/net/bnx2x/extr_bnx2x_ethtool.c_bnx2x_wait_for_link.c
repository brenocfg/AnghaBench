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
typedef  scalar_t__ u8 ;
struct TYPE_2__ {int /*<<< orphan*/  link_up; } ;
struct bnx2x {TYPE_1__ link_vars; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MSG_ETHTOOL ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ bnx2x_link_test (struct bnx2x*,scalar_t__) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void bnx2x_wait_for_link(struct bnx2x *bp, u8 link_up, u8 is_serdes)
{
	int cnt = 1400;

	if (link_up) {
		while (bnx2x_link_test(bp, is_serdes) && cnt--)
			msleep(20);

		if (cnt <= 0 && bnx2x_link_test(bp, is_serdes))
			DP(BNX2X_MSG_ETHTOOL, "Timeout waiting for link up\n");

		cnt = 1400;
		while (!bp->link_vars.link_up && cnt--)
			msleep(20);

		if (cnt <= 0 && !bp->link_vars.link_up)
			DP(BNX2X_MSG_ETHTOOL,
			   "Timeout waiting for link init\n");
	}
}