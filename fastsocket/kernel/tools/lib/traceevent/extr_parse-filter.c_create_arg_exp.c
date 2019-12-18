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
struct TYPE_2__ {int type; } ;
struct filter_arg {TYPE_1__ op; int /*<<< orphan*/  type; } ;
typedef  enum filter_exp_type { ____Placeholder_filter_exp_type } filter_exp_type ;

/* Variables and functions */
 int /*<<< orphan*/  FILTER_ARG_EXP ; 
 struct filter_arg* allocate_arg () ; 

__attribute__((used)) static struct filter_arg *
create_arg_exp(enum filter_exp_type etype)
{
	struct filter_arg *arg;

	arg = allocate_arg();
	arg->type = FILTER_ARG_EXP;
	arg->op.type = etype;

	return arg;
}