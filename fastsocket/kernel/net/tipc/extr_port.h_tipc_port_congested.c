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
struct port {int sent; int acked; } ;

/* Variables and functions */
 int TIPC_FLOW_CONTROL_WIN ; 

__attribute__((used)) static inline int tipc_port_congested(struct port *p_ptr)
{
	return((p_ptr->sent - p_ptr->acked) >= (TIPC_FLOW_CONTROL_WIN * 2));
}