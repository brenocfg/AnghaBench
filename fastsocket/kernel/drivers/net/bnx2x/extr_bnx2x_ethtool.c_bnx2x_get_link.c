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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  link_up; } ;
struct bnx2x {int flags; scalar_t__ state; TYPE_1__ link_vars; } ;

/* Variables and functions */
 scalar_t__ BNX2X_STATE_OPEN ; 
 int MF_FUNC_DIS ; 
 struct bnx2x* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u32 bnx2x_get_link(struct net_device *dev)
{
	struct bnx2x *bp = netdev_priv(dev);

	if (bp->flags & MF_FUNC_DIS || (bp->state != BNX2X_STATE_OPEN))
		return 0;

	return bp->link_vars.link_up;
}