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
struct tipc_name_seq {int /*<<< orphan*/  upper; int /*<<< orphan*/  lower; int /*<<< orphan*/  type; } ;
struct publication {int /*<<< orphan*/  pport_list; } ;
struct TYPE_2__ {int published; int /*<<< orphan*/  ref; scalar_t__ connected; } ;
struct port {scalar_t__ pub_count; TYPE_1__ publ; int /*<<< orphan*/  publications; } ;

/* Variables and functions */
 int EADDRINUSE ; 
 int EINVAL ; 
 unsigned int TIPC_NODE_SCOPE ; 
 unsigned int TIPC_ZONE_SCOPE ; 
 int /*<<< orphan*/  dbg (char*,scalar_t__,struct port*,scalar_t__,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct publication* tipc_nametbl_publish (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,scalar_t__) ; 
 struct port* tipc_port_lock (scalar_t__) ; 
 int /*<<< orphan*/  tipc_port_unlock (struct port*) ; 

int tipc_publish(u32 ref, unsigned int scope, struct tipc_name_seq const *seq)
{
	struct port *p_ptr;
	struct publication *publ;
	u32 key;
	int res = -EINVAL;

	p_ptr = tipc_port_lock(ref);
	if (!p_ptr)
		return -EINVAL;

	dbg("tipc_publ %u, p_ptr = %x, conn = %x, scope = %x, "
	    "lower = %u, upper = %u\n",
	    ref, p_ptr, p_ptr->publ.connected, scope, seq->lower, seq->upper);
	if (p_ptr->publ.connected)
		goto exit;
	if (seq->lower > seq->upper)
		goto exit;
	if ((scope < TIPC_ZONE_SCOPE) || (scope > TIPC_NODE_SCOPE))
		goto exit;
	key = ref + p_ptr->pub_count + 1;
	if (key == ref) {
		res = -EADDRINUSE;
		goto exit;
	}
	publ = tipc_nametbl_publish(seq->type, seq->lower, seq->upper,
				    scope, p_ptr->publ.ref, key);
	if (publ) {
		list_add(&publ->pport_list, &p_ptr->publications);
		p_ptr->pub_count++;
		p_ptr->publ.published = 1;
		res = 0;
	}
exit:
	tipc_port_unlock(p_ptr);
	return res;
}