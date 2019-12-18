#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct disasm_line {int /*<<< orphan*/  ops; TYPE_2__* ins; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* parse ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 TYPE_2__* ins__find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void disasm_line__init_ins(struct disasm_line *dl)
{
	dl->ins = ins__find(dl->name);

	if (dl->ins == NULL)
		return;

	if (!dl->ins->ops)
		return;

	if (dl->ins->ops->parse)
		dl->ins->ops->parse(&dl->ops);
}