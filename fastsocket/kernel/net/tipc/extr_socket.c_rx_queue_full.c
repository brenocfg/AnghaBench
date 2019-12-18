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
 scalar_t__ TIPC_HIGH_IMPORTANCE ; 
 scalar_t__ TIPC_LOW_IMPORTANCE ; 
 scalar_t__ TIPC_MEDIUM_IMPORTANCE ; 
 scalar_t__ msg_connected (struct tipc_msg*) ; 
 scalar_t__ msg_importance (struct tipc_msg*) ; 

__attribute__((used)) static int rx_queue_full(struct tipc_msg *msg, u32 queue_size, u32 base)
{
	u32 threshold;
	u32 imp = msg_importance(msg);

	if (imp == TIPC_LOW_IMPORTANCE)
		threshold = base;
	else if (imp == TIPC_MEDIUM_IMPORTANCE)
		threshold = base * 2;
	else if (imp == TIPC_HIGH_IMPORTANCE)
		threshold = base * 100;
	else
		return 0;

	if (msg_connected(msg))
		threshold *= 4;

	return (queue_size >= threshold);
}