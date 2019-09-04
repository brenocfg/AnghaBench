#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tre_mem_t ;
struct TYPE_4__ {int code_min; int code_max; int position; } ;
typedef  TYPE_1__ tre_literal_t ;
typedef  int /*<<< orphan*/  tre_ast_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  LITERAL ; 
 int /*<<< orphan*/ * tre_ast_new_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* tre_mem_calloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static tre_ast_node_t *
tre_ast_new_literal(tre_mem_t mem, int code_min, int code_max, int position)
{
	tre_ast_node_t *node;
	tre_literal_t *lit;

	lit = tre_mem_calloc(mem, sizeof *lit);
	node = tre_ast_new_node(mem, LITERAL, lit);
	if (!node)
		return 0;
	lit->code_min = code_min;
	lit->code_max = code_max;
	lit->position = position;
	return node;
}