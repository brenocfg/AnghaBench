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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int congested; int /*<<< orphan*/  connected; } ;
struct port {TYPE_1__ publ; int /*<<< orphan*/  sent; } ;
struct iovec {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ELINKCONG ; 
 scalar_t__ likely (int) ; 
 int msg_calc_data_size (struct iovec const*,unsigned int) ; 
 int /*<<< orphan*/  port_incr_out_seqno (struct port*) ; 
 scalar_t__ port_peernode (struct port*) ; 
 scalar_t__ port_unreliable (struct port*) ; 
 int tipc_link_send_sections_fast (struct port*,struct iovec const*,unsigned int,scalar_t__) ; 
 scalar_t__ tipc_own_addr ; 
 int /*<<< orphan*/  tipc_port_congested (struct port*) ; 
 struct port* tipc_port_deref (scalar_t__) ; 
 int tipc_port_recv_sections (struct port*,unsigned int,struct iovec const*) ; 

int tipc_send(u32 ref, unsigned int num_sect, struct iovec const *msg_sect)
{
	struct port *p_ptr;
	u32 destnode;
	int res;

	p_ptr = tipc_port_deref(ref);
	if (!p_ptr || !p_ptr->publ.connected)
		return -EINVAL;

	p_ptr->publ.congested = 1;
	if (!tipc_port_congested(p_ptr)) {
		destnode = port_peernode(p_ptr);
		if (likely(destnode != tipc_own_addr))
			res = tipc_link_send_sections_fast(p_ptr, msg_sect, num_sect,
							   destnode);
		else
			res = tipc_port_recv_sections(p_ptr, num_sect, msg_sect);

		if (likely(res != -ELINKCONG)) {
			port_incr_out_seqno(p_ptr);
			p_ptr->publ.congested = 0;
			p_ptr->sent++;
			return res;
		}
	}
	if (port_unreliable(p_ptr)) {
		p_ptr->publ.congested = 0;
		/* Just calculate msg length and return */
		return msg_calc_data_size(msg_sect, num_sect);
	}
	return -ELINKCONG;
}