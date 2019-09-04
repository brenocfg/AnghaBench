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
struct TYPE_9__ {TYPE_2__* n; int /*<<< orphan*/  mem; } ;
typedef  TYPE_1__ tre_parse_ctx_t ;
struct TYPE_10__ {int submatch_id; int /*<<< orphan*/  num_submatches; } ;
typedef  TYPE_2__ tre_ast_node_t ;
typedef  int /*<<< orphan*/  reg_errcode_t ;

/* Variables and functions */
 int /*<<< orphan*/  EMPTY ; 
 int /*<<< orphan*/  REG_ESPACE ; 
 int /*<<< orphan*/  REG_OK ; 
 TYPE_2__* tre_ast_new_catenation (int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*) ; 
 TYPE_2__* tre_ast_new_literal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static reg_errcode_t marksub(tre_parse_ctx_t *ctx, tre_ast_node_t *node, int subid)
{
	if (node->submatch_id >= 0) {
		tre_ast_node_t *n = tre_ast_new_literal(ctx->mem, EMPTY, -1, -1);
		if (!n)
			return REG_ESPACE;
		n = tre_ast_new_catenation(ctx->mem, n, node);
		if (!n)
			return REG_ESPACE;
		n->num_submatches = node->num_submatches;
		node = n;
	}
	node->submatch_id = subid;
	node->num_submatches++;
	ctx->n = node;
	return REG_OK;
}