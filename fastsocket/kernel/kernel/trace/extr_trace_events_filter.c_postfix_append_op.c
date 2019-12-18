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
struct postfix_elt {int op; int /*<<< orphan*/  list; int /*<<< orphan*/ * operand; } ;
struct filter_parse_state {int /*<<< orphan*/  postfix; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct postfix_elt* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int postfix_append_op(struct filter_parse_state *ps, int op)
{
	struct postfix_elt *elt;

	elt = kmalloc(sizeof(*elt), GFP_KERNEL);
	if (!elt)
		return -ENOMEM;

	elt->op = op;
	elt->operand = NULL;

	list_add_tail(&elt->list, &ps->postfix);

	return 0;
}