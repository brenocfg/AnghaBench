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
struct TYPE_4__ {int type; int nullable; int submatch_id; void* obj; } ;
typedef  TYPE_1__ tre_ast_node_t ;

/* Variables and functions */
 TYPE_1__* tre_mem_calloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static tre_ast_node_t *
tre_ast_new_node(tre_mem_t mem, int type, void *obj)
{
	tre_ast_node_t *node = tre_mem_calloc(mem, sizeof *node);
	if (!node || !obj)
		return 0;
	node->obj = obj;
	node->type = type;
	node->nullable = -1;
	node->submatch_id = -1;
	return node;
}