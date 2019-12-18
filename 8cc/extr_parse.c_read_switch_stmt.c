#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vector ;
struct TYPE_16__ {int /*<<< orphan*/  ty; } ;
typedef  TYPE_1__ Node ;

/* Variables and functions */
 int /*<<< orphan*/  RESTORE_SWITCH_CONTEXT () ; 
 int /*<<< orphan*/  SET_SWITCH_CONTEXT (char*) ; 
 TYPE_1__* ast_binop (int /*<<< orphan*/ ,char,TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* ast_compound_stmt (int /*<<< orphan*/ *) ; 
 TYPE_1__* ast_dest (char*) ; 
 TYPE_1__* ast_jump (char*) ; 
 TYPE_1__* ast_lvar (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cases ; 
 TYPE_1__* conv (int /*<<< orphan*/ ) ; 
 char* defaultcase ; 
 int /*<<< orphan*/  ensure_inttype (TYPE_1__*) ; 
 int /*<<< orphan*/  expect (char) ; 
 char* make_label () ; 
 TYPE_1__* make_switch_jump (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_tempname () ; 
 int /*<<< orphan*/ * make_vector () ; 
 int /*<<< orphan*/  read_expr () ; 
 TYPE_1__* read_stmt () ; 
 int /*<<< orphan*/  vec_get (int /*<<< orphan*/ ,int) ; 
 int vec_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vec_push (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static Node *read_switch_stmt() {
    expect('(');
    Node *expr = conv(read_expr());
    ensure_inttype(expr);
    expect(')');

    char *end = make_label();
    SET_SWITCH_CONTEXT(end);
    Node *body = read_stmt();
    Vector *v = make_vector();
    Node *var = ast_lvar(expr->ty, make_tempname());
    vec_push(v, ast_binop(expr->ty, '=', var, expr));
    for (int i = 0; i < vec_len(cases); i++)
        vec_push(v, make_switch_jump(var, vec_get(cases, i)));
    vec_push(v, ast_jump(defaultcase ? defaultcase : end));
    if (body)
        vec_push(v, body);
    vec_push(v, ast_dest(end));
    RESTORE_SWITCH_CONTEXT();
    return ast_compound_stmt(v);
}