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
struct TYPE_2__ {int /*<<< orphan*/  stats; } ;

/* Variables and functions */
 int ENOPROTOOPT ; 
 int /*<<< orphan*/  bc_lock ; 
 TYPE_1__* bcl ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int tipc_bclink_reset_stats(void)
{
	if (!bcl)
		return -ENOPROTOOPT;

	spin_lock_bh(&bc_lock);
	memset(&bcl->stats, 0, sizeof(bcl->stats));
	spin_unlock_bh(&bc_lock);
	return 0;
}