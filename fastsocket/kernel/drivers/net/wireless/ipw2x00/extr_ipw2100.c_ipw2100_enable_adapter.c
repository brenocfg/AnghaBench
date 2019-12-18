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
struct ipw2100_priv {int status; int /*<<< orphan*/  adapter_mutex; int /*<<< orphan*/  hang_check; scalar_t__ stop_hang_check; TYPE_1__* net_dev; } ;
struct host_command {int /*<<< orphan*/  host_command_length; int /*<<< orphan*/  host_command_sequence; int /*<<< orphan*/  host_command; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOST_COMPLETE ; 
 int HZ ; 
 int /*<<< orphan*/  IPW_DEBUG_HC (char*) ; 
 int /*<<< orphan*/  IPW_DEBUG_INFO (char*,...) ; 
 int /*<<< orphan*/  IPW_HW_STATE_ENABLED ; 
 int STATUS_ENABLED ; 
 int ipw2100_hw_send_command (struct ipw2100_priv*,struct host_command*) ; 
 int ipw2100_wait_for_card_state (struct ipw2100_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ rf_kill_active (struct ipw2100_priv*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ipw2100_enable_adapter(struct ipw2100_priv *priv)
{
	struct host_command cmd = {
		.host_command = HOST_COMPLETE,
		.host_command_sequence = 0,
		.host_command_length = 0
	};
	int err = 0;

	IPW_DEBUG_HC("HOST_COMPLETE\n");

	if (priv->status & STATUS_ENABLED)
		return 0;

	mutex_lock(&priv->adapter_mutex);

	if (rf_kill_active(priv)) {
		IPW_DEBUG_HC("Command aborted due to RF kill active.\n");
		goto fail_up;
	}

	err = ipw2100_hw_send_command(priv, &cmd);
	if (err) {
		IPW_DEBUG_INFO("Failed to send HOST_COMPLETE command\n");
		goto fail_up;
	}

	err = ipw2100_wait_for_card_state(priv, IPW_HW_STATE_ENABLED);
	if (err) {
		IPW_DEBUG_INFO("%s: card not responding to init command.\n",
			       priv->net_dev->name);
		goto fail_up;
	}

	if (priv->stop_hang_check) {
		priv->stop_hang_check = 0;
		schedule_delayed_work(&priv->hang_check, HZ / 2);
	}

      fail_up:
	mutex_unlock(&priv->adapter_mutex);
	return err;
}