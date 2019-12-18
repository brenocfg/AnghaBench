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
 scalar_t__ msg_destnode (struct tipc_msg*) ; 
 scalar_t__ msg_short (struct tipc_msg*) ; 

__attribute__((used)) static inline int msg_is_dest(struct tipc_msg *m, u32 d)
{
	return(msg_short(m) || (msg_destnode(m) == d));
}