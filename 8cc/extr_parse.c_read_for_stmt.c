#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vector ;
struct TYPE_15__ {int /*<<< orphan*/  ty; } ;
typedef  TYPE_1__ Node ;
typedef  int /*<<< orphan*/  Map ;

/* Variables and functions */
 int /*<<< orphan*/  RESTORE_JUMP_LABELS () ; 
 int /*<<< orphan*/  SET_JUMP_LABELS (char*,char*) ; 
 TYPE_1__* ast_compound_stmt (int /*<<< orphan*/ *) ; 
 TYPE_1__* ast_conv (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* ast_dest (char*) ; 
 TYPE_1__* ast_if (TYPE_1__*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* ast_jump (char*) ; 
 int /*<<< orphan*/  expect (char) ; 
 scalar_t__ is_flotype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * localenv ; 
 char* make_label () ; 
 int /*<<< orphan*/ * make_map_parent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * make_vector () ; 
 TYPE_1__* read_expr_opt () ; 
 TYPE_1__* read_opt_decl_or_stmt () ; 
 TYPE_1__* read_stmt () ; 
 int /*<<< orphan*/  type_bool ; 
 int /*<<< orphan*/  vec_push (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static Node *read_for_stmt() {
    expect('(');
    char *beg = make_label();
    char *mid = make_label();
    char *end = make_label();
    Map *orig = localenv;
    localenv = make_map_parent(localenv);
    Node *init = read_opt_decl_or_stmt();
    Node *cond = read_expr_opt();
    if (cond && is_flotype(cond->ty))
        cond = ast_conv(type_bool, cond);
    expect(';');
    Node *step = read_expr_opt();
    expect(')');
    SET_JUMP_LABELS(mid, end);
    Node *body = read_stmt();
    RESTORE_JUMP_LABELS();
    localenv = orig;

    Vector *v = make_vector();
    if (init)
        vec_push(v, init);
    vec_push(v, ast_dest(beg));
    if (cond)
        vec_push(v, ast_if(cond, NULL, ast_jump(end)));
    if (body)
        vec_push(v, body);
    vec_push(v, ast_dest(mid));
    if (step)
        vec_push(v, step);
    vec_push(v, ast_jump(beg));
    vec_push(v, ast_dest(end));
    return ast_compound_stmt(v);
}