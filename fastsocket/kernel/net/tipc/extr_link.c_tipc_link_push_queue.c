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
typedef  scalar_t__ u32 ;
struct link {int /*<<< orphan*/  b_ptr; } ;

/* Variables and functions */
 scalar_t__ PUSH_FAILED ; 
 scalar_t__ tipc_bearer_congested (int /*<<< orphan*/ ,struct link*) ; 
 int /*<<< orphan*/  tipc_bearer_schedule (int /*<<< orphan*/ ,struct link*) ; 
 scalar_t__ tipc_link_push_packet (struct link*) ; 

void tipc_link_push_queue(struct link *l_ptr)
{
	u32 res;

	if (tipc_bearer_congested(l_ptr->b_ptr, l_ptr))
		return;

	do {
		res = tipc_link_push_packet(l_ptr);
	} while (!res);

	if (res == PUSH_FAILED)
		tipc_bearer_schedule(l_ptr->b_ptr, l_ptr);
}