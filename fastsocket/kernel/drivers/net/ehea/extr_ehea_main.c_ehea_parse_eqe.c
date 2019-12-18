#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct ehea_port {int full_duplex; TYPE_1__* netdev; int /*<<< orphan*/  phy_link; int /*<<< orphan*/  port_speed; } ;
struct ehea_adapter {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EHEA_BMASK_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  EHEA_EC_ADAPTER_MALFUNC 130 
#define  EHEA_EC_PORTSTATE_CHG 129 
#define  EHEA_EC_PORT_MALFUNC 128 
 int /*<<< orphan*/  EHEA_PHY_LINK_DOWN ; 
 int /*<<< orphan*/  EHEA_PHY_LINK_UP ; 
 int /*<<< orphan*/  NEQE_EVENT_CODE ; 
 int /*<<< orphan*/  NEQE_EXTSWITCH_PORT_UP ; 
 int /*<<< orphan*/  NEQE_EXTSWITCH_PRIMARY ; 
 int /*<<< orphan*/  NEQE_PORTNUM ; 
 int /*<<< orphan*/  NEQE_PORT_UP ; 
 int /*<<< orphan*/  ehea_error (char*,...) ; 
 struct ehea_port* ehea_get_port (struct ehea_adapter*,int) ; 
 int /*<<< orphan*/  ehea_info (char*,...) ; 
 int ehea_sense_port_attr (struct ehea_port*) ; 
 int /*<<< orphan*/  netif_carrier_off (TYPE_1__*) ; 
 int /*<<< orphan*/  netif_carrier_ok (TYPE_1__*) ; 
 int /*<<< orphan*/  netif_carrier_on (TYPE_1__*) ; 
 int /*<<< orphan*/  netif_msg_link (struct ehea_port*) ; 
 int /*<<< orphan*/  netif_tx_disable (TYPE_1__*) ; 
 int /*<<< orphan*/  netif_wake_queue (TYPE_1__*) ; 
 int /*<<< orphan*/  prop_carrier_state ; 

__attribute__((used)) static void ehea_parse_eqe(struct ehea_adapter *adapter, u64 eqe)
{
	int ret;
	u8 ec;
	u8 portnum;
	struct ehea_port *port;

	ec = EHEA_BMASK_GET(NEQE_EVENT_CODE, eqe);
	portnum = EHEA_BMASK_GET(NEQE_PORTNUM, eqe);
	port = ehea_get_port(adapter, portnum);

	switch (ec) {
	case EHEA_EC_PORTSTATE_CHG:	/* port state change */

		if (!port) {
			ehea_error("unknown portnum %x", portnum);
			break;
		}

		if (EHEA_BMASK_GET(NEQE_PORT_UP, eqe)) {
			if (!netif_carrier_ok(port->netdev)) {
				ret = ehea_sense_port_attr(port);
				if (ret) {
					ehea_error("failed resensing port "
						   "attributes");
					break;
				}

				if (netif_msg_link(port))
					ehea_info("%s: Logical port up: %dMbps "
						  "%s Duplex",
						  port->netdev->name,
						  port->port_speed,
						  port->full_duplex ==
						  1 ? "Full" : "Half");

				netif_carrier_on(port->netdev);
				netif_wake_queue(port->netdev);
			}
		} else
			if (netif_carrier_ok(port->netdev)) {
				if (netif_msg_link(port))
					ehea_info("%s: Logical port down",
						  port->netdev->name);
				netif_carrier_off(port->netdev);
				netif_tx_disable(port->netdev);
			}

		if (EHEA_BMASK_GET(NEQE_EXTSWITCH_PORT_UP, eqe)) {
			port->phy_link = EHEA_PHY_LINK_UP;
			if (netif_msg_link(port))
				ehea_info("%s: Physical port up",
					  port->netdev->name);
			if (prop_carrier_state)
				netif_carrier_on(port->netdev);
		} else {
			port->phy_link = EHEA_PHY_LINK_DOWN;
			if (netif_msg_link(port))
				ehea_info("%s: Physical port down",
					  port->netdev->name);
			if (prop_carrier_state)
				netif_carrier_off(port->netdev);
		}

		if (EHEA_BMASK_GET(NEQE_EXTSWITCH_PRIMARY, eqe))
			ehea_info("External switch port is primary port");
		else
			ehea_info("External switch port is backup port");

		break;
	case EHEA_EC_ADAPTER_MALFUNC:
		ehea_error("Adapter malfunction");
		break;
	case EHEA_EC_PORT_MALFUNC:
		ehea_info("Port malfunction: Device: %s", port->netdev->name);
		netif_carrier_off(port->netdev);
		netif_tx_disable(port->netdev);
		break;
	default:
		ehea_error("unknown event code %x, eqe=0x%llX", ec, eqe);
		break;
	}
}