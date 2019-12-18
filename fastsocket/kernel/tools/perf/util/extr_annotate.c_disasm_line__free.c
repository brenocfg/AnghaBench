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
struct disasm_line {int /*<<< orphan*/  ops; TYPE_2__* ins; struct disasm_line* name; struct disasm_line* line; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* free ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct disasm_line*) ; 
 int /*<<< orphan*/  ins__delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

void disasm_line__free(struct disasm_line *dl)
{
	free(dl->line);
	free(dl->name);
	if (dl->ins && dl->ins->ops->free)
		dl->ins->ops->free(&dl->ops);
	else
		ins__delete(&dl->ops);
	free(dl);
}