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
typedef  scalar_t__ u16 ;
struct slave {scalar_t__ link; int speed; } ;
struct port {int /*<<< orphan*/  actor_port_number; struct slave* slave; } ;

/* Variables and functions */
 scalar_t__ AD_LINK_SPEED_BITMASK_10000MBPS ; 
 scalar_t__ AD_LINK_SPEED_BITMASK_1000MBPS ; 
 scalar_t__ AD_LINK_SPEED_BITMASK_100MBPS ; 
 scalar_t__ AD_LINK_SPEED_BITMASK_10MBPS ; 
 scalar_t__ BOND_LINK_UP ; 
#define  SPEED_10 131 
#define  SPEED_100 130 
#define  SPEED_1000 129 
#define  SPEED_10000 128 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static u16 __get_link_speed(struct port *port)
{
	struct slave *slave = port->slave;
	u16 speed;

	/* this if covers only a special case: when the configuration starts with
	 * link down, it sets the speed to 0.
	 * This is done in spite of the fact that the e100 driver reports 0 to be
	 * compatible with MVT in the future.*/
	if (slave->link != BOND_LINK_UP) {
		speed=0;
	} else {
		switch (slave->speed) {
		case SPEED_10:
			speed = AD_LINK_SPEED_BITMASK_10MBPS;
			break;

		case SPEED_100:
			speed = AD_LINK_SPEED_BITMASK_100MBPS;
			break;

		case SPEED_1000:
			speed = AD_LINK_SPEED_BITMASK_1000MBPS;
			break;

		case SPEED_10000:
			speed = AD_LINK_SPEED_BITMASK_10000MBPS;
			break;

		default:
			speed = 0; // unknown speed value from ethtool. shouldn't happen
			break;
		}
	}

	pr_debug("Port %d Received link speed %d update from adapter\n", port->actor_port_number, speed);
	return speed;
}