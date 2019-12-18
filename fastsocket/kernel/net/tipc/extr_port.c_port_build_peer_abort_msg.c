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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ref; int /*<<< orphan*/  connected; int /*<<< orphan*/  phdr; } ;
struct port {TYPE_1__ publ; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIPC_CONN_MSG ; 
 scalar_t__ TIPC_CRITICAL_IMPORTANCE ; 
 scalar_t__ msg_importance (int /*<<< orphan*/ *) ; 
 struct sk_buff* port_build_proto_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  port_out_seqno (struct port*) ; 
 int /*<<< orphan*/  port_peernode (struct port*) ; 
 int /*<<< orphan*/  port_peerport (struct port*) ; 
 int /*<<< orphan*/  tipc_own_addr ; 

__attribute__((used)) static struct sk_buff *port_build_peer_abort_msg(struct port *p_ptr, u32 err)
{
	u32 imp = msg_importance(&p_ptr->publ.phdr);

	if (!p_ptr->publ.connected)
		return NULL;
	if (imp < TIPC_CRITICAL_IMPORTANCE)
		imp++;
	return port_build_proto_msg(port_peerport(p_ptr),
				    port_peernode(p_ptr),
				    p_ptr->publ.ref,
				    tipc_own_addr,
				    imp,
				    TIPC_CONN_MSG,
				    err,
				    port_out_seqno(p_ptr),
				    0);
}