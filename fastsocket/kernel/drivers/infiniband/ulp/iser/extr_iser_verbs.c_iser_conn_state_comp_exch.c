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
struct iser_conn {int state; int /*<<< orphan*/  lock; } ;
typedef  enum iser_ib_conn_state { ____Placeholder_iser_ib_conn_state } iser_ib_conn_state ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iser_conn_state_comp_exch(struct iser_conn *ib_conn,
				     enum iser_ib_conn_state comp,
				     enum iser_ib_conn_state exch)
{
	int ret;

	spin_lock_bh(&ib_conn->lock);
	if ((ret = (ib_conn->state == comp)))
		ib_conn->state = exch;
	spin_unlock_bh(&ib_conn->lock);
	return ret;
}