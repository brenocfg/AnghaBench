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
struct rds_loop_connection {int /*<<< orphan*/  loop_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct rds_loop_connection*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  loop_conns_lock ; 
 int /*<<< orphan*/  rdsdebug (char*,struct rds_loop_connection*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void rds_loop_conn_free(void *arg)
{
	struct rds_loop_connection *lc = arg;
	unsigned long flags;

	rdsdebug("lc %p\n", lc);
	spin_lock_irqsave(&loop_conns_lock, flags);
	list_del(&lc->loop_node);
	spin_unlock_irqrestore(&loop_conns_lock, flags);
	kfree(lc);
}