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
typedef  int u8 ;
struct slave {scalar_t__ link; int duplex; } ;
struct port {int /*<<< orphan*/  actor_port_number; struct slave* slave; } ;

/* Variables and functions */
 scalar_t__ BOND_LINK_UP ; 
#define  DUPLEX_FULL 129 
#define  DUPLEX_HALF 128 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 __get_duplex(struct port *port)
{
	struct slave *slave = port->slave;

	u8 retval;

	//  handling a special case: when the configuration starts with
	// link down, it sets the duplex to 0.
	if (slave->link != BOND_LINK_UP) {
		retval=0x0;
	} else {
		switch (slave->duplex) {
		case DUPLEX_FULL:
			retval=0x1;
			pr_debug("Port %d Received status full duplex update from adapter\n", port->actor_port_number);
			break;
		case DUPLEX_HALF:
		default:
			retval=0x0;
			pr_debug("Port %d Received status NOT full duplex update from adapter\n", port->actor_port_number);
			break;
		}
	}
	return retval;
}