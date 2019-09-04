#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tre_mem_t ;
struct TYPE_8__ {int min; int max; int minimal; TYPE_2__* arg; } ;
typedef  TYPE_1__ tre_iteration_t ;
struct TYPE_9__ {int /*<<< orphan*/  num_submatches; } ;
typedef  TYPE_2__ tre_ast_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  ITERATION ; 
 TYPE_2__* tre_ast_new_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* tre_mem_calloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static tre_ast_node_t *
tre_ast_new_iter(tre_mem_t mem, tre_ast_node_t *arg, int min, int max, int minimal)
{
	tre_ast_node_t *node;
	tre_iteration_t *iter;

	iter = tre_mem_calloc(mem, sizeof *iter);
	node = tre_ast_new_node(mem, ITERATION, iter);
	if (!node)
		return 0;
	iter->arg = arg;
	iter->min = min;
	iter->max = max;
	iter->minimal = minimal;
	node->num_submatches = arg->num_submatches;
	return node;
}