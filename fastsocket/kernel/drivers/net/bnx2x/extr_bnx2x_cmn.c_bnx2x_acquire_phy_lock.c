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
struct TYPE_2__ {int /*<<< orphan*/  phy_mutex; } ;
struct bnx2x {TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  HW_LOCK_RESOURCE_MDIO ; 
 int /*<<< orphan*/  bnx2x_acquire_hw_lock (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 

void bnx2x_acquire_phy_lock(struct bnx2x *bp)
{
	mutex_lock(&bp->port.phy_mutex);

	bnx2x_acquire_hw_lock(bp, HW_LOCK_RESOURCE_MDIO);
}