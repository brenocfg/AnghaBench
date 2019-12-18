#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ beg; scalar_t__ end; int /*<<< orphan*/  label; } ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_1__ Case ;

/* Variables and functions */
 int /*<<< orphan*/  OP_EQ ; 
 int /*<<< orphan*/  OP_LE ; 
 int /*<<< orphan*/  OP_LOGAND ; 
 int /*<<< orphan*/ * ast_binop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ast_if (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ast_inttype (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ast_jump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  type_int ; 

__attribute__((used)) static Node *make_switch_jump(Node *var, Case *c) {
    Node *cond;
    if (c->beg == c->end) {
        cond = ast_binop(type_int, OP_EQ, var, ast_inttype(type_int, c->beg));
    } else {
        // [GNU] case i ... j is compiled to if (i <= cond && cond <= j) goto <label>.
        Node *x = ast_binop(type_int, OP_LE, ast_inttype(type_int, c->beg), var);
        Node *y = ast_binop(type_int, OP_LE, var, ast_inttype(type_int, c->end));
        cond = ast_binop(type_int, OP_LOGAND, x, y);
    }
    return ast_if(cond, ast_jump(c->label), NULL);
}