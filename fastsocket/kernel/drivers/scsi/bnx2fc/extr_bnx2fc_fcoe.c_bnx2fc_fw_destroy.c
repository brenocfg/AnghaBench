#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned long data; int /*<<< orphan*/  function; scalar_t__ expires; } ;
struct bnx2fc_hba {TYPE_1__ destroy_timer; int /*<<< orphan*/  flags; int /*<<< orphan*/  destroy_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2FC_FLAG_DESTROY_CMPL ; 
 int /*<<< orphan*/  BNX2FC_FLAG_FW_INIT_DONE ; 
 scalar_t__ BNX2FC_FW_TIMEOUT ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  bnx2fc_destroy_timer ; 
 scalar_t__ bnx2fc_send_fw_fcoe_destroy_msg (struct bnx2fc_hba*) ; 
 int /*<<< orphan*/  bnx2fc_unbind_adapter_devices (struct bnx2fc_hba*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  del_timer_sync (TYPE_1__*) ; 
 int /*<<< orphan*/  flush_signals (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2fc_fw_destroy(struct bnx2fc_hba *hba)
{
	if (test_and_clear_bit(BNX2FC_FLAG_FW_INIT_DONE, &hba->flags)) {
		if (bnx2fc_send_fw_fcoe_destroy_msg(hba) == 0) {
			init_timer(&hba->destroy_timer);
			hba->destroy_timer.expires = BNX2FC_FW_TIMEOUT +
								jiffies;
			hba->destroy_timer.function = bnx2fc_destroy_timer;
			hba->destroy_timer.data = (unsigned long)hba;
			add_timer(&hba->destroy_timer);
			wait_event_interruptible(hba->destroy_wait,
					test_bit(BNX2FC_FLAG_DESTROY_CMPL,
						 &hba->flags));
			clear_bit(BNX2FC_FLAG_DESTROY_CMPL, &hba->flags);
			/* This should never happen */
			if (signal_pending(current))
				flush_signals(current);

			del_timer_sync(&hba->destroy_timer);
		}
		bnx2fc_unbind_adapter_devices(hba);
	}
}