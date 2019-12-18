#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct il_force_reset {scalar_t__ last_force_reset_jiffies; int /*<<< orphan*/  reset_success_count; int /*<<< orphan*/  reset_reject_count; scalar_t__ reset_duration; int /*<<< orphan*/  reset_request_count; } ;
struct il_priv {int /*<<< orphan*/  restart; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  status; int /*<<< orphan*/  wait_command_queue; TYPE_2__* cfg; struct il_force_reset force_reset; } ;
struct TYPE_4__ {TYPE_1__* mod_params; } ;
struct TYPE_3__ {int /*<<< orphan*/  restart_fw; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_INFO (char*) ; 
 int EAGAIN ; 
 int EINVAL ; 
 int /*<<< orphan*/  IL_ERR (char*) ; 
 int /*<<< orphan*/  S_EXIT_PENDING ; 
 int /*<<< orphan*/  S_FW_ERROR ; 
 int /*<<< orphan*/  S_READY ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

int
il_force_reset(struct il_priv *il, bool external)
{
	struct il_force_reset *force_reset;

	if (test_bit(S_EXIT_PENDING, &il->status))
		return -EINVAL;

	force_reset = &il->force_reset;
	force_reset->reset_request_count++;
	if (!external) {
		if (force_reset->last_force_reset_jiffies &&
		    time_after(force_reset->last_force_reset_jiffies +
			       force_reset->reset_duration, jiffies)) {
			D_INFO("force reset rejected\n");
			force_reset->reset_reject_count++;
			return -EAGAIN;
		}
	}
	force_reset->reset_success_count++;
	force_reset->last_force_reset_jiffies = jiffies;

	/*
	 * if the request is from external(ex: debugfs),
	 * then always perform the request in regardless the module
	 * parameter setting
	 * if the request is from internal (uCode error or driver
	 * detect failure), then fw_restart module parameter
	 * need to be check before performing firmware reload
	 */

	if (!external && !il->cfg->mod_params->restart_fw) {
		D_INFO("Cancel firmware reload based on "
		       "module parameter setting\n");
		return 0;
	}

	IL_ERR("On demand firmware reload\n");

	/* Set the FW error flag -- cleared on il_down */
	set_bit(S_FW_ERROR, &il->status);
	wake_up(&il->wait_command_queue);
	/*
	 * Keep the restart process from trying to send host
	 * commands by clearing the INIT status bit
	 */
	clear_bit(S_READY, &il->status);
	queue_work(il->workqueue, &il->restart);

	return 0;
}