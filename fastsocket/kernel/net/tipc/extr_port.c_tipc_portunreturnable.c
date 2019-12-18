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
typedef  int /*<<< orphan*/  u32 ;
struct port {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int port_unreturnable (struct port*) ; 
 struct port* tipc_port_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_port_unlock (struct port*) ; 

int tipc_portunreturnable(u32 ref, unsigned int *isunrejectable)
{
	struct port *p_ptr;

	p_ptr = tipc_port_lock(ref);
	if (!p_ptr)
		return -EINVAL;
	*isunrejectable = port_unreturnable(p_ptr);
	tipc_port_unlock(p_ptr);
	return 0;
}