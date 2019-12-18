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

__attribute__((used)) static int mv88e6123_61_65_setup_global(struct dsa_switch *ds)
{
	int ret;
	int i;

	/*
	 * Disable the PHY polling unit (since there won't be any
	 * external PHYs to poll), don't discard packets with
	 * excessive collisions, and mask all interrupt sources.
	 */
	REG_WRITE(REG_GLOBAL, 0x04, 0x0000);

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
	 * Configure the upstream port, and configure the upstream
	 * port as the port to which ingress and egress monitor frames
	 * are to be sent.
	 */
	REG_WRITE(REG_GLOBAL, 0x1a, (dsa_upstream_port(ds) * 0x1110));

	/*
	 * Disable remote management for now, and set the switch's
	 * DSA device number.
	 */
	REG_WRITE(REG_GLOBAL, 0x1c, ds->index & 0x1f);

	/*
	 * Send all frames with destination addresses matching
	 * 01:80:c2:00:00:2x to the CPU port.
	 */
	REG_WRITE(REG_GLOBAL2, 0x02, 0xffff);

	/*
	 * Send all frames with destination addresses matching
	 * 01:80:c2:00:00:0x to the CPU port.
	 */
	REG_WRITE(REG_GLOBAL2, 0x03, 0xffff);

	/*
	 * Disable the loopback filter, disable flow control
	 * messages, disable flood broadcast override, disable
	 * removing of provider tags, disable ATU age violation
	 * interrupts, disable tag flow control, force flow
	 * control priority to the highest, and send all special
	 * multicast frames to the CPU at the highest priority.
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
		REG_WRITE(REG_GLOBAL2, 0x07, 0x8000 | (i << 12) | 0xff);

	/*
	 * Clear all trunk mappings.
	 */
	for (i = 0; i < 16; i++)
		REG_WRITE(REG_GLOBAL2, 0x08, 0x8000 | (i << 11));

	/*
	 * Disable ingress rate limiting by resetting all ingress
	 * rate limit registers to their initial state.
	 */
	for (i = 0; i < 6; i++)
		REG_WRITE(REG_GLOBAL2, 0x09, 0x9000 | (i << 8));

	/*
	 * Initialise cross-chip port VLAN table to reset defaults.
	 */
	REG_WRITE(REG_GLOBAL2, 0x0b, 0x9000);

	/*
	 * Clear the priority override table.
	 */
	for (i = 0; i < 16; i++)
		REG_WRITE(REG_GLOBAL2, 0x0f, 0x8000 | (i << 8));

	/* @@@ initialise AVB (22/23) watchdog (27) sdet (29) registers */

	return 0;
}