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
struct rds_sock {int /*<<< orphan*/  rs_cong_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_cong_monitor ; 
 int /*<<< orphan*/  rds_cong_monitor_lock ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void rds_cong_add_socket(struct rds_sock *rs)
{
	unsigned long flags;

	write_lock_irqsave(&rds_cong_monitor_lock, flags);
	if (list_empty(&rs->rs_cong_list))
		list_add(&rs->rs_cong_list, &rds_cong_monitor);
	write_unlock_irqrestore(&rds_cong_monitor_lock, flags);
}