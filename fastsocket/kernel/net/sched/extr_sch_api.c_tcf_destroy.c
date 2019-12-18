#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tcf_proto {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  owner; int /*<<< orphan*/  (* destroy ) (struct tcf_proto*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct tcf_proto*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct tcf_proto*) ; 

void tcf_destroy(struct tcf_proto *tp)
{
	tp->ops->destroy(tp);
	module_put(tp->ops->owner);
	kfree(tp);
}