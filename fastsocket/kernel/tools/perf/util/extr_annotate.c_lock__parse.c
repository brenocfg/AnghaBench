#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* ops; TYPE_5__* ins; } ;
struct ins_operands {TYPE_2__ locked; int /*<<< orphan*/  raw; } ;
struct TYPE_10__ {TYPE_1__* ops; } ;
struct TYPE_9__ {int /*<<< orphan*/  raw; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* parse ) (TYPE_3__*) ;} ;

/* Variables and functions */
 scalar_t__ disasm_line__parse (int /*<<< orphan*/ ,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 TYPE_5__* ins__find (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 TYPE_3__* zalloc (int) ; 

__attribute__((used)) static int lock__parse(struct ins_operands *ops)
{
	char *name;

	ops->locked.ops = zalloc(sizeof(*ops->locked.ops));
	if (ops->locked.ops == NULL)
		return 0;

	if (disasm_line__parse(ops->raw, &name, &ops->locked.ops->raw) < 0)
		goto out_free_ops;

	ops->locked.ins = ins__find(name);
	if (ops->locked.ins == NULL)
		goto out_free_ops;

	if (!ops->locked.ins->ops)
		return 0;

	if (ops->locked.ins->ops->parse)
		ops->locked.ins->ops->parse(ops->locked.ops);

	return 0;

out_free_ops:
	free(ops->locked.ops);
	ops->locked.ops = NULL;
	return 0;
}