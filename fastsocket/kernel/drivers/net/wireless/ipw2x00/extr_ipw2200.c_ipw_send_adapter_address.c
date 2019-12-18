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
typedef  int /*<<< orphan*/  u8 ;
struct ipw_priv {TYPE_1__* net_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  IPW_CMD_ADAPTER_ADDRESS ; 
 int /*<<< orphan*/  IPW_DEBUG_INFO (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPW_ERROR (char*) ; 
 int ipw_send_cmd_pdu (struct ipw_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipw_send_adapter_address(struct ipw_priv *priv, u8 * mac)
{
	if (!priv || !mac) {
		IPW_ERROR("Invalid args\n");
		return -1;
	}

	IPW_DEBUG_INFO("%s: Setting MAC to %pM\n",
		       priv->net_dev->name, mac);

	return ipw_send_cmd_pdu(priv, IPW_CMD_ADAPTER_ADDRESS, ETH_ALEN, mac);
}