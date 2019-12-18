#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dsa_switch {int index; TYPE_3__* pd; TYPE_2__* dst; } ;
struct TYPE_6__ {int* rtable; } ;
struct TYPE_5__ {TYPE_1__* pd; } ;
struct TYPE_4__ {int nr_chips; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_GLOBAL ; 
 int /*<<< orphan*/  REG_GLOBAL2 ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int,int) ; 
 int dsa_upstream_port (struct dsa_switch*) ; 
 int mv88e6xxx_config_prio (struct dsa_switch*) ; 

__attribute__((used)) static int mv88e6131_setup_global(struct dsa_switch *ds)
{
	int ret;
	int i;

	/*
	 * Enable the PHY polling unit, don't discard packets with
	 * excessive collisions, use a weighted fair queueing scheme
	 * to arbitrate between packet queues, set the maximum frame
	 * size to 1632, and mask all interrupt sources.
	 */
	REG_WRITE(REG_GLOBAL, 0x04, 0x4400);

	/*
	 * Set the default address aging time to 5 minutes, and
	 * enable address learn messages to be sent to all message
	 * ports.
	 */
	REG_WRITE(REG_GLOBAL, 0x0a, 0x0148);

	/*
	 * Configure the priority mapping registers.
	 */
	ret = mv88e6xxx_config_prio(ds);
	if (ret < 0)
		return ret;

	/*
	 * Set the VLAN ethertype to 0x8100.
	 */
	REG_WRITE(REG_GLOBAL, 0x19, 0x8100);

	/*
	 * Disable ARP mirroring, and configure the upstream port as
	 * the port to which ingress and egress monitor frames are to
	 * be sent.
	 */
	REG_WRITE(REG_GLOBAL, 0x1a, (dsa_upstream_port(ds) * 0x1100) | 0x00f0);

	/*
	 * Disable cascade port functionality, and set the switch's
	 * DSA device number.
	 */
	REG_WRITE(REG_GLOBAL, 0x1c, 0xe000 | (ds->index & 0x1f));

	/*
	 * Send all frames with destination addresses matching
	 * 01:80:c2:00:00:0x to the CPU port.
	 */
	REG_WRITE(REG_GLOBAL2, 0x03, 0xffff);

	/*
	 * Ignore removed tag data on doubly tagged packets, disable
	 * flow control messages, force flow control priority to the
	 * highest, and send all special multicast frames to the CPU
	 * port at the higest priority.
	 */
	REG_WRITE(REG_GLOBAL2, 0x05, 0x00ff);

	/*
	 * Program the DSA routing table.
	 */
	for (i = 0; i < 32; i++) {
		int nexthop;

		nexthop = 0x1f;
		if (i != ds->index && i < ds->dst->pd->nr_chips)
			nexthop = ds->pd->rtable[i] & 0x1f;

		REG_WRITE(REG_GLOBAL2, 0x06, 0x8000 | (i << 8) | nexthop);
	}

	/*
	 * Clear all trunk masks.
	 */
	for (i = 0; i < 8; i++)
		REG_WRITE(REG_GLOBAL2, 0x07, 0x8000 | (i << 12) | 0x7ff);

	/*
	 * Clear all trunk mappings.
	 */
	for (i = 0; i < 16; i++)
		REG_WRITE(REG_GLOBAL2, 0x08, 0x8000 | (i << 11));

	/*
	 * Force the priority of IGMP/MLD snoop frames and ARP frames
	 * to the highest setting.
	 */
	REG_WRITE(REG_GLOBAL2, 0x0f, 0x00ff);

	return 0;
}