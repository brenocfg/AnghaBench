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
struct TYPE_2__ {struct filter_arg* right; } ;
struct filter_arg {TYPE_1__ op; } ;

/* Variables and functions */

__attribute__((used)) static struct filter_arg *
rotate_op_right(struct filter_arg *a, struct filter_arg *b)
{
	struct filter_arg *arg;

	arg = a->op.right;
	a->op.right = b;
	return arg;
}