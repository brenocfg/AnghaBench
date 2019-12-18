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
typedef  int u16 ;
struct dsa_switch {int dsa_port_mask; int phys_port_mask; TYPE_1__* dst; } ;
struct TYPE_2__ {scalar_t__ tag_protocol; } ;

/* Variables and functions */
 int ETH_P_EDSA ; 
 int REG_PORT (int) ; 
 int /*<<< orphan*/  REG_WRITE (int,int,int) ; 
 scalar_t__ dsa_is_cpu_port (struct dsa_switch*,int) ; 
 int dsa_upstream_port (struct dsa_switch*) ; 
 scalar_t__ htons (int) ; 

__attribute__((used)) static int mv88e6123_61_65_setup_port(struct dsa_switch *ds, int p)
{
	int addr = REG_PORT(p);
	u16 val;

	/*
	 * MAC Forcing register: don't force link, speed, duplex
	 * or flow control state to any particular values on physical
	 * ports, but force the CPU port and all DSA ports to 1000 Mb/s
	 * full duplex.
	 */
	if (dsa_is_cpu_port(ds, p) || ds->dsa_port_mask & (1 << p))
		REG_WRITE(addr, 0x01, 0x003e);
	else
		REG_WRITE(addr, 0x01, 0x0003);

	/*
	 * Do not limit the period of time that this port can be
	 * paused for by the remote end or the period of time that
	 * this port can pause the remote end.
	 */
	REG_WRITE(addr, 0x02, 0x0000);

	/*
	 * Port Control: disable Drop-on-Unlock, disable Drop-on-Lock,
	 * disable Header mode, enable IGMP/MLD snooping, disable VLAN
	 * tunneling, determine priority by looking at 802.1p and IP
	 * priority fields (IP prio has precedence), and set STP state
	 * to Forwarding.
	 *
	 * If this is the CPU link, use DSA or EDSA tagging depending
	 * on which tagging mode was configured.
	 *
	 * If this is a link to another switch, use DSA tagging mode.
	 *
	 * If this is the upstream port for this switch, enable
	 * forwarding of unknown unicasts and multicasts.
	 */
	val = 0x0433;
	if (dsa_is_cpu_port(ds, p)) {
		if (ds->dst->tag_protocol == htons(ETH_P_EDSA))
			val |= 0x3300;
		else
			val |= 0x0100;
	}
	if (ds->dsa_port_mask & (1 << p))
		val |= 0x0100;
	if (p == dsa_upstream_port(ds))
		val |= 0x000c;
	REG_WRITE(addr, 0x04, val);

	/*
	 * Port Control 1: disable trunking.  Also, if this is the
	 * CPU port, enable learn messages to be sent to this port.
	 */
	REG_WRITE(addr, 0x05, dsa_is_cpu_port(ds, p) ? 0x8000 : 0x0000);

	/*
	 * Port based VLAN map: give each port its own address
	 * database, allow the CPU port to talk to each of the 'real'
	 * ports, and allow each of the 'real' ports to only talk to
	 * the upstream port.
	 */
	val = (p & 0xf) << 12;
	if (dsa_is_cpu_port(ds, p))
		val |= ds->phys_port_mask;
	else
		val |= 1 << dsa_upstream_port(ds);
	REG_WRITE(addr, 0x06, val);

	/*
	 * Default VLAN ID and priority: don't set a default VLAN
	 * ID, and set the default packet priority to zero.
	 */
	REG_WRITE(addr, 0x07, 0x0000);

	/*
	 * Port Control 2: don't force a good FCS, set the maximum
	 * frame size to 10240 bytes, don't let the switch add or
	 * strip 802.1q tags, don't discard tagged or untagged frames
	 * on this port, do a destination address lookup on all
	 * received packets as usual, disable ARP mirroring and don't
	 * send a copy of all transmitted/received frames on this port
	 * to the CPU.
	 */
	REG_WRITE(addr, 0x08, 0x2080);

	/*
	 * Egress rate control: disable egress rate control.
	 */
	REG_WRITE(addr, 0x09, 0x0001);

	/*
	 * Egress rate control 2: disable egress rate control.
	 */
	REG_WRITE(addr, 0x0a, 0x0000);

	/*
	 * Port Association Vector: when learning source addresses
	 * of packets, add the address to the address database using
	 * a port bitmap that has only the bit for this port set and
	 * the other bits clear.
	 */
	REG_WRITE(addr, 0x0b, 1 << p);

	/*
	 * Port ATU control: disable limiting the number of address
	 * database entries that this port is allowed to use.
	 */
	REG_WRITE(addr, 0x0c, 0x0000);

	/*
	 * Priorit Override: disable DA, SA and VTU priority override.
	 */
	REG_WRITE(addr, 0x0d, 0x0000);

	/*
	 * Port Ethertype: use the Ethertype DSA Ethertype value.
	 */
	REG_WRITE(addr, 0x0f, ETH_P_EDSA);

	/*
	 * Tag Remap: use an identity 802.1p prio -> switch prio
	 * mapping.
	 */
	REG_WRITE(addr, 0x18, 0x3210);

	/*
	 * Tag Remap 2: use an identity 802.1p prio -> switch prio
	 * mapping.
	 */
	REG_WRITE(addr, 0x19, 0x7654);

	return 0;
}