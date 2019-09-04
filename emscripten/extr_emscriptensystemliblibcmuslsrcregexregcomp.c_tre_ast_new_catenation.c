#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tre_mem_t ;
struct TYPE_9__ {TYPE_2__* right; TYPE_2__* left; } ;
typedef  TYPE_1__ tre_catenation_t ;
struct TYPE_10__ {scalar_t__ num_submatches; } ;
typedef  TYPE_2__ tre_ast_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  CATENATION ; 
 TYPE_2__* tre_ast_new_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* tre_mem_calloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static tre_ast_node_t *
tre_ast_new_catenation(tre_mem_t mem, tre_ast_node_t *left, tre_ast_node_t *right)
{
	tre_ast_node_t *node;
	tre_catenation_t *cat;

	if (!left)
		return right;
	cat = tre_mem_calloc(mem, sizeof *cat);
	node = tre_ast_new_node(mem, CATENATION, cat);
	if (!node)
		return 0;
	cat->left = left;
	cat->right = right;
	node->num_submatches = left->num_submatches + right->num_submatches;
	return node;
}