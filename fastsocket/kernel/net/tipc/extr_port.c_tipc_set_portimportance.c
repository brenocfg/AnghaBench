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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  phdr; } ;
struct port {TYPE_1__ publ; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int TIPC_CRITICAL_IMPORTANCE ; 
 int /*<<< orphan*/  msg_set_importance (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct port* tipc_port_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_port_unlock (struct port*) ; 

int tipc_set_portimportance(u32 ref, unsigned int imp)
{
	struct port *p_ptr;

	if (imp > TIPC_CRITICAL_IMPORTANCE)
		return -EINVAL;

	p_ptr = tipc_port_lock(ref);
	if (!p_ptr)
		return -EINVAL;
	msg_set_importance(&p_ptr->publ.phdr, (u32)imp);
	tipc_port_unlock(p_ptr);
	return 0;
}