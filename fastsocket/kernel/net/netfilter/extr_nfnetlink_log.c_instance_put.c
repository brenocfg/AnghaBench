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
struct nfulnl_instance {int /*<<< orphan*/  use; } ;

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct nfulnl_instance*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
instance_put(struct nfulnl_instance *inst)
{
	if (inst && atomic_dec_and_test(&inst->use)) {
		kfree(inst);
		module_put(THIS_MODULE);
	}
}