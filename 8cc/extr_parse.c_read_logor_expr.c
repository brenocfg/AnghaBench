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
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  OP_LOGOR ; 
 int /*<<< orphan*/ * ast_binop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ next_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * read_logand_expr () ; 
 int /*<<< orphan*/  type_int ; 

__attribute__((used)) static Node *read_logor_expr() {
    Node *node = read_logand_expr();
    while (next_token(OP_LOGOR))
        node = ast_binop(type_int, OP_LOGOR, node, read_logand_expr());
    return node;
}