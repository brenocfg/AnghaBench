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
struct tipc_msg {int dummy; } ;

/* Variables and functions */
 scalar_t__ FIRST_FRAGMENT ; 
 scalar_t__ MSG_FRAGMENTER ; 
 scalar_t__ likely (int) ; 
 struct tipc_msg* msg_get_wrapped (struct tipc_msg*) ; 
 scalar_t__ msg_importance (struct tipc_msg*) ; 
 int msg_isdata (struct tipc_msg*) ; 
 scalar_t__ msg_orignode (struct tipc_msg*) ; 
 scalar_t__ msg_type (struct tipc_msg*) ; 
 scalar_t__ msg_user (struct tipc_msg*) ; 
 scalar_t__ tipc_own_addr ; 

__attribute__((used)) static inline u32 msg_tot_importance(struct tipc_msg *m)
{
	if (likely(msg_isdata(m))) {
		if (likely(msg_orignode(m) == tipc_own_addr))
			return msg_importance(m);
		return msg_importance(m) + 4;
	}
	if ((msg_user(m) == MSG_FRAGMENTER)  &&
	    (msg_type(m) == FIRST_FRAGMENT))
		return msg_importance(msg_get_wrapped(m));
	return msg_importance(m);
}