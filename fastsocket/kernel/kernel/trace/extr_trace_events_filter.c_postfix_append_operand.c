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
struct postfix_elt {int /*<<< orphan*/  list; int /*<<< orphan*/  operand; int /*<<< orphan*/  op; } ;
struct filter_parse_state {int /*<<< orphan*/  postfix; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  OP_NONE ; 
 int /*<<< orphan*/  kfree (struct postfix_elt*) ; 
 struct postfix_elt* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kstrdup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int postfix_append_operand(struct filter_parse_state *ps, char *operand)
{
	struct postfix_elt *elt;

	elt = kmalloc(sizeof(*elt), GFP_KERNEL);
	if (!elt)
		return -ENOMEM;

	elt->op = OP_NONE;
	elt->operand = kstrdup(operand, GFP_KERNEL);
	if (!elt->operand) {
		kfree(elt);
		return -ENOMEM;
	}

	list_add_tail(&elt->list, &ps->postfix);

	return 0;
}