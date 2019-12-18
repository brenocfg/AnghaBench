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
struct TYPE_2__ {void* usr_handle; } ;
struct port {TYPE_1__ publ; } ;

/* Variables and functions */
 struct port* tipc_port_lock (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  tipc_port_unlock (struct port*) ; 

void *tipc_get_handle(const u32 ref)
{
	struct port *p_ptr;
	void * handle;

	p_ptr = tipc_port_lock(ref);
	if (!p_ptr)
		return NULL;
	handle = p_ptr->publ.usr_handle;
	tipc_port_unlock(p_ptr);
	return handle;
}