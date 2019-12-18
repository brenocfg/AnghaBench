#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * buf; } ;
struct TYPE_5__ {TYPE_1__ print_buf; } ;

/* Variables and functions */
 scalar_t__ BCLINK_LOG_BUF_SIZE ; 
 int /*<<< orphan*/  bc_lock ; 
 int /*<<< orphan*/ * bcbearer ; 
 TYPE_2__* bcl ; 
 int /*<<< orphan*/ * bclink ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_link_stop (TYPE_2__*) ; 

void tipc_bclink_stop(void)
{
	spin_lock_bh(&bc_lock);
	if (bcbearer) {
		tipc_link_stop(bcl);
		if (BCLINK_LOG_BUF_SIZE)
			kfree(bcl->print_buf.buf);
		bcl = NULL;
		kfree(bclink);
		bclink = NULL;
		kfree(bcbearer);
		bcbearer = NULL;
	}
	spin_unlock_bh(&bc_lock);
}