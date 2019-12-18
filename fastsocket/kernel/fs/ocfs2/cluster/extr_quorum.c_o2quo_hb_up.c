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
typedef  int /*<<< orphan*/  u8 ;
struct o2quo_state {scalar_t__ qs_heartbeating; int /*<<< orphan*/  qs_lock; int /*<<< orphan*/  qs_conn_bm; int /*<<< orphan*/  qs_hb_bm; } ;

/* Variables and functions */
 scalar_t__ O2NM_MAX_NODES ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mlog_bug_on_msg (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  o2quo_clear_hold (struct o2quo_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  o2quo_set_hold (struct o2quo_state*,int /*<<< orphan*/ ) ; 
 struct o2quo_state o2quo_state ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void o2quo_hb_up(u8 node)
{
	struct o2quo_state *qs = &o2quo_state;

	spin_lock(&qs->qs_lock);

	qs->qs_heartbeating++;
	mlog_bug_on_msg(qs->qs_heartbeating == O2NM_MAX_NODES,
		        "node %u\n", node);
	mlog_bug_on_msg(test_bit(node, qs->qs_hb_bm), "node %u\n", node);
	set_bit(node, qs->qs_hb_bm);

	mlog(0, "node %u, %d total\n", node, qs->qs_heartbeating);

	if (!test_bit(node, qs->qs_conn_bm))
		o2quo_set_hold(qs, node);
	else
		o2quo_clear_hold(qs, node);

	spin_unlock(&qs->qs_lock);
}