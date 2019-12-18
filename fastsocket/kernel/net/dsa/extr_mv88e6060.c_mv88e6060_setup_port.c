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
struct dsa_switch {int phys_port_mask; TYPE_1__* dst; } ;
struct TYPE_2__ {int cpu_port; } ;

/* Variables and functions */
 int REG_PORT (int) ; 
 int /*<<< orphan*/  REG_WRITE (int,int,int) ; 
 scalar_t__ dsa_is_cpu_port (struct dsa_switch*,int) ; 

__attribute__((used)) static int mv88e6060_setup_port(struct dsa_switch *ds, int p)
{
	int addr = REG_PORT(p);

	/*
	 * Do not force flow control, disable Ingress and Egress
	 * Header tagging, disable VLAN tunneling, and set the port
	 * state to Forwarding.  Additionally, if this is the CPU
	 * port, enable Ingress and Egress Trailer tagging mode.
	 */
	REG_WRITE(addr, 0x04, dsa_is_cpu_port(ds, p) ?  0x4103 : 0x0003);

	/*
	 * Port based VLAN map: give each port its own address
	 * database, allow the CPU port to talk to each of the 'real'
	 * ports, and allow each of the 'real' ports to only talk to
	 * the CPU port.
	 */
	REG_WRITE(addr, 0x06,
			((p & 0xf) << 12) |
			 (dsa_is_cpu_port(ds, p) ?
				ds->phys_port_mask :
				(1 << ds->dst->cpu_port)));

	/*
	 * Port Association Vector: when learning source addresses
	 * of packets, add the address to the address database using
	 * a port bitmap that has only the bit for this port set and
	 * the other bits clear.
	 */
	REG_WRITE(addr, 0x0b, 1 << p);

	return 0;
}