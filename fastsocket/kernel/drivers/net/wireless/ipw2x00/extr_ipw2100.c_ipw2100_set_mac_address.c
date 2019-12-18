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
struct ipw2100_priv {int config; TYPE_1__* net_dev; int /*<<< orphan*/  mac_addr; } ;
struct host_command {int /*<<< orphan*/  host_command_parameters; int /*<<< orphan*/  host_command_length; int /*<<< orphan*/  host_command_sequence; int /*<<< orphan*/  host_command; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADAPTER_ADDRESS ; 
 int CFG_CUSTOM_MAC ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  IPW_DEBUG_HC (char*) ; 
 int /*<<< orphan*/  IPW_DEBUG_INFO (char*) ; 
 int ipw2100_hw_send_command (struct ipw2100_priv*,struct host_command*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipw2100_set_mac_address(struct ipw2100_priv *priv, int batch_mode)
{
	struct host_command cmd = {
		.host_command = ADAPTER_ADDRESS,
		.host_command_sequence = 0,
		.host_command_length = ETH_ALEN
	};
	int err;

	IPW_DEBUG_HC("SET_MAC_ADDRESS\n");

	IPW_DEBUG_INFO("enter\n");

	if (priv->config & CFG_CUSTOM_MAC) {
		memcpy(cmd.host_command_parameters, priv->mac_addr, ETH_ALEN);
		memcpy(priv->net_dev->dev_addr, priv->mac_addr, ETH_ALEN);
	} else
		memcpy(cmd.host_command_parameters, priv->net_dev->dev_addr,
		       ETH_ALEN);

	err = ipw2100_hw_send_command(priv, &cmd);

	IPW_DEBUG_INFO("exit\n");
	return err;
}