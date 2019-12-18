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
typedef  int u32 ;
struct tipc_msg {int dummy; } ;

/* Variables and functions */
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int msg_destnode (struct tipc_msg*) ; 
 int msg_orignode (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_short (struct tipc_msg*) ; 

__attribute__((used)) static inline u32 msg_routed(struct tipc_msg *m)
{
	if (likely(msg_short(m)))
		return 0;
	return(msg_destnode(m) ^ msg_orignode(m)) >> 11;
}