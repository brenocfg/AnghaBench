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
struct nfulnl_instance {scalar_t__ skb; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  __nfulnl_send (struct nfulnl_instance*) ; 
 scalar_t__ del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  instance_put (struct nfulnl_instance*) ; 

__attribute__((used)) static void
__nfulnl_flush(struct nfulnl_instance *inst)
{
	/* timer holds a reference */
	if (del_timer(&inst->timer))
		instance_put(inst);
	if (inst->skb)
		__nfulnl_send(inst);
}