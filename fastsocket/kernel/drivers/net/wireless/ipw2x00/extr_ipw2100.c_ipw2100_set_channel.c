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
typedef  scalar_t__ u32 ;
struct ipw2100_priv {scalar_t__ channel; int /*<<< orphan*/  config; TYPE_1__* ieee; } ;
struct host_command {int host_command_length; scalar_t__* host_command_parameters; int /*<<< orphan*/  host_command_sequence; int /*<<< orphan*/  host_command; } ;
struct TYPE_2__ {scalar_t__ iw_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_STATIC_CHANNEL ; 
 int /*<<< orphan*/  CHANNEL ; 
 int EINVAL ; 
 int /*<<< orphan*/  IPW_DEBUG_HC (char*,scalar_t__) ; 
 int /*<<< orphan*/  IPW_DEBUG_INFO (char*,scalar_t__) ; 
 scalar_t__ IW_MODE_INFRA ; 
 scalar_t__ REG_MAX_CHANNEL ; 
 scalar_t__ REG_MIN_CHANNEL ; 
 int ipw2100_disable_adapter (struct ipw2100_priv*) ; 
 int ipw2100_enable_adapter (struct ipw2100_priv*) ; 
 int ipw2100_hw_send_command (struct ipw2100_priv*,struct host_command*) ; 

__attribute__((used)) static int ipw2100_set_channel(struct ipw2100_priv *priv, u32 channel,
			       int batch_mode)
{
	struct host_command cmd = {
		.host_command = CHANNEL,
		.host_command_sequence = 0,
		.host_command_length = sizeof(u32)
	};
	int err;

	cmd.host_command_parameters[0] = channel;

	IPW_DEBUG_HC("CHANNEL: %d\n", channel);

	/* If BSS then we don't support channel selection */
	if (priv->ieee->iw_mode == IW_MODE_INFRA)
		return 0;

	if ((channel != 0) &&
	    ((channel < REG_MIN_CHANNEL) || (channel > REG_MAX_CHANNEL)))
		return -EINVAL;

	if (!batch_mode) {
		err = ipw2100_disable_adapter(priv);
		if (err)
			return err;
	}

	err = ipw2100_hw_send_command(priv, &cmd);
	if (err) {
		IPW_DEBUG_INFO("Failed to set channel to %d", channel);
		return err;
	}

	if (channel)
		priv->config |= CFG_STATIC_CHANNEL;
	else
		priv->config &= ~CFG_STATIC_CHANNEL;

	priv->channel = channel;

	if (!batch_mode) {
		err = ipw2100_enable_adapter(priv);
		if (err)
			return err;
	}

	return 0;
}