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
struct tipc_portid {int /*<<< orphan*/  ref; int /*<<< orphan*/  node; } ;
struct tipc_name {int /*<<< orphan*/  instance; int /*<<< orphan*/  type; } ;
struct tipc_msg {int dummy; } ;
struct TYPE_2__ {struct tipc_msg phdr; scalar_t__ connected; } ;
struct port {int /*<<< orphan*/  sent; TYPE_1__ publ; } ;
struct iovec {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ELINKCONG ; 
 int /*<<< orphan*/  LONG_H_SIZE ; 
 unsigned int TIPC_CRITICAL_IMPORTANCE ; 
 int /*<<< orphan*/  TIPC_ERR_NO_NAME ; 
 int /*<<< orphan*/  TIPC_NAMED_MSG ; 
 int /*<<< orphan*/  addr_scope (scalar_t__) ; 
 scalar_t__ likely (int) ; 
 int msg_calc_data_size (struct iovec const*,scalar_t__) ; 
 int /*<<< orphan*/  msg_set_destnode (struct tipc_msg*,scalar_t__) ; 
 int /*<<< orphan*/  msg_set_destport (struct tipc_msg*,scalar_t__) ; 
 int /*<<< orphan*/  msg_set_hdr_sz (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_importance (struct tipc_msg*,unsigned int) ; 
 int /*<<< orphan*/  msg_set_lookup_scope (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_nameinst (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_nametype (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_orignode (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_origport (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_type (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 scalar_t__ port_unreliable (struct port*) ; 
 int tipc_link_send_sections_fast (struct port*,struct iovec const*,scalar_t__,scalar_t__) ; 
 scalar_t__ tipc_nametbl_translate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ tipc_own_addr ; 
 struct port* tipc_port_deref (scalar_t__) ; 
 int tipc_port_recv_sections (struct port*,scalar_t__,struct iovec const*) ; 
 int tipc_port_reject_sections (struct port*,struct tipc_msg*,struct iovec const*,scalar_t__,int /*<<< orphan*/ ) ; 

int tipc_forward2name(u32 ref,
		      struct tipc_name const *name,
		      u32 domain,
		      u32 num_sect,
		      struct iovec const *msg_sect,
		      struct tipc_portid const *orig,
		      unsigned int importance)
{
	struct port *p_ptr;
	struct tipc_msg *msg;
	u32 destnode = domain;
	u32 destport = 0;
	int res;

	p_ptr = tipc_port_deref(ref);
	if (!p_ptr || p_ptr->publ.connected)
		return -EINVAL;

	msg = &p_ptr->publ.phdr;
	msg_set_type(msg, TIPC_NAMED_MSG);
	msg_set_orignode(msg, orig->node);
	msg_set_origport(msg, orig->ref);
	msg_set_hdr_sz(msg, LONG_H_SIZE);
	msg_set_nametype(msg, name->type);
	msg_set_nameinst(msg, name->instance);
	msg_set_lookup_scope(msg, addr_scope(domain));
	if (importance <= TIPC_CRITICAL_IMPORTANCE)
		msg_set_importance(msg,importance);
	destport = tipc_nametbl_translate(name->type, name->instance, &destnode);
	msg_set_destnode(msg, destnode);
	msg_set_destport(msg, destport);

	if (likely(destport || destnode)) {
		p_ptr->sent++;
		if (likely(destnode == tipc_own_addr))
			return tipc_port_recv_sections(p_ptr, num_sect, msg_sect);
		res = tipc_link_send_sections_fast(p_ptr, msg_sect, num_sect,
						   destnode);
		if (likely(res != -ELINKCONG))
			return res;
		if (port_unreliable(p_ptr)) {
			/* Just calculate msg length and return */
			return msg_calc_data_size(msg_sect, num_sect);
		}
		return -ELINKCONG;
	}
	return tipc_port_reject_sections(p_ptr, msg, msg_sect, num_sect,
					 TIPC_ERR_NO_NAME);
}