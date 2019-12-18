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
typedef  int u64 ;
struct veth_port {int mac_addr; int num_mcast; int* mcast_addr; int /*<<< orphan*/  mcast_gate; scalar_t__ promiscuous; } ;

/* Variables and functions */
 int /*<<< orphan*/  read_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline int veth_frame_wanted(struct veth_port *port, u64 mac_addr)
{
	int wanted = 0;
	int i;
	unsigned long flags;

	if ( (mac_addr == port->mac_addr) || (mac_addr == 0xffffffffffff0000) )
		return 1;

	read_lock_irqsave(&port->mcast_gate, flags);

	if (port->promiscuous) {
		wanted = 1;
		goto out;
	}

	for (i = 0; i < port->num_mcast; ++i) {
		if (port->mcast_addr[i] == mac_addr) {
			wanted = 1;
			break;
		}
	}

 out:
	read_unlock_irqrestore(&port->mcast_gate, flags);

	return wanted;
}