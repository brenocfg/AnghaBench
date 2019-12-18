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
 int /*<<< orphan*/  msg_set_dest_droppable (int /*<<< orphan*/ *,int) ; 
 struct port* tipc_port_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_port_unlock (struct port*) ; 

int tipc_set_portunreturnable(u32 ref, unsigned int isunrejectable)
{
	struct port *p_ptr;

	p_ptr = tipc_port_lock(ref);
	if (!p_ptr)
		return -EINVAL;
	msg_set_dest_droppable(&p_ptr->publ.phdr, (isunrejectable != 0));
	tipc_port_unlock(p_ptr);
	return 0;
}