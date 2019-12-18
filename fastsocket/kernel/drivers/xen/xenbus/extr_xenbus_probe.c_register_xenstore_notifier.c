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
struct notifier_block {int (* notifier_call ) (struct notifier_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  blocking_notifier_chain_register (int /*<<< orphan*/ *,struct notifier_block*) ; 
 int stub1 (struct notifier_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xenstore_chain ; 
 scalar_t__ xenstored_ready ; 

int register_xenstore_notifier(struct notifier_block *nb)
{
	int ret = 0;

	if (xenstored_ready > 0)
		ret = nb->notifier_call(nb, 0, NULL);
	else
		blocking_notifier_chain_register(&xenstore_chain, nb);

	return ret;
}