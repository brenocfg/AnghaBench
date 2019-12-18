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
typedef  int /*<<< orphan*/  Vector ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  RESTORE_JUMP_LABELS () ; 
 int /*<<< orphan*/  SET_JUMP_LABELS (char*,char*) ; 
 int /*<<< orphan*/ * ast_compound_stmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ast_dest (char*) ; 
 int /*<<< orphan*/  ast_if (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ast_jump (char*) ; 
 int /*<<< orphan*/  expect (char) ; 
 char* make_label () ; 
 int /*<<< orphan*/ * make_vector () ; 
 int /*<<< orphan*/ * read_boolean_expr () ; 
 int /*<<< orphan*/ * read_stmt () ; 
 int /*<<< orphan*/  vec_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Node *read_while_stmt() {
    expect('(');
    Node *cond = read_boolean_expr();
    expect(')');

    char *beg = make_label();
    char *end = make_label();
    SET_JUMP_LABELS(beg, end);
    Node *body = read_stmt();
    RESTORE_JUMP_LABELS();

    Vector *v = make_vector();
    vec_push(v, ast_dest(beg));
    vec_push(v, ast_if(cond, body, ast_jump(end)));
    vec_push(v, ast_jump(beg));
    vec_push(v, ast_dest(end));
    return ast_compound_stmt(v);
}