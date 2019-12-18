#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xt_tgdtor_param {TYPE_3__* target; int /*<<< orphan*/  targinfo; } ;
struct TYPE_4__ {TYPE_3__* target; } ;
struct TYPE_5__ {TYPE_1__ kernel; } ;
struct ipt_entry_target {int /*<<< orphan*/  data; TYPE_2__ u; } ;
struct TYPE_6__ {int /*<<< orphan*/  me; int /*<<< orphan*/  (* destroy ) (struct xt_tgdtor_param*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct xt_tgdtor_param*) ; 

__attribute__((used)) static void ipt_destroy_target(struct ipt_entry_target *t)
{
	struct xt_tgdtor_param par = {
		.target   = t->u.kernel.target,
		.targinfo = t->data,
	};
	if (par.target->destroy != NULL)
		par.target->destroy(&par);
	module_put(par.target->me);
}