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
struct ipw2100_priv {int /*<<< orphan*/  bssid; } ;
struct host_command {int host_command_length; int /*<<< orphan*/  host_command_parameters; int /*<<< orphan*/  host_command_sequence; int /*<<< orphan*/  host_command; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISASSOCIATION_BSSID ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  IPW_DEBUG_HC (char*) ; 
 int ipw2100_hw_send_command (struct ipw2100_priv*,struct host_command*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ipw2100_disassociate_bssid(struct ipw2100_priv *priv)
{
	struct host_command cmd = {
		.host_command = DISASSOCIATION_BSSID,
		.host_command_sequence = 0,
		.host_command_length = ETH_ALEN
	};
	int err;
	int len;

	IPW_DEBUG_HC("DISASSOCIATION_BSSID\n");

	len = ETH_ALEN;
	/* The Firmware currently ignores the BSSID and just disassociates from
	 * the currently associated AP -- but in the off chance that a future
	 * firmware does use the BSSID provided here, we go ahead and try and
	 * set it to the currently associated AP's BSSID */
	memcpy(cmd.host_command_parameters, priv->bssid, ETH_ALEN);

	err = ipw2100_hw_send_command(priv, &cmd);

	return err;
}