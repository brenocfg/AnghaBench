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
struct bnx2fc_rport {int /*<<< orphan*/  ofld_timer; int /*<<< orphan*/  flags; int /*<<< orphan*/  ofld_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2FC_FLAG_OFLD_REQ_CMPL ; 
 scalar_t__ BNX2FC_FW_TIMEOUT ; 
 int /*<<< orphan*/  bnx2fc_ofld_timer ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_signals (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  setup_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2fc_ofld_wait(struct bnx2fc_rport *tgt)
{
	setup_timer(&tgt->ofld_timer, bnx2fc_ofld_timer, (unsigned long)tgt);
	mod_timer(&tgt->ofld_timer, jiffies + BNX2FC_FW_TIMEOUT);

	wait_event_interruptible(tgt->ofld_wait,
				 (test_bit(
				  BNX2FC_FLAG_OFLD_REQ_CMPL,
				  &tgt->flags)));
	if (signal_pending(current))
		flush_signals(current);
	del_timer_sync(&tgt->ofld_timer);
}