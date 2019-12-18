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
typedef  int /*<<< orphan*/  Token ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  KWHILE ; 
 int /*<<< orphan*/  RESTORE_JUMP_LABELS () ; 
 int /*<<< orphan*/  SET_JUMP_LABELS (char*,char*) ; 
 int /*<<< orphan*/ * ast_compound_stmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ast_dest (char*) ; 
 int /*<<< orphan*/ * ast_if (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ast_jump (char*) ; 
 int /*<<< orphan*/  errort (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expect (char) ; 
 int /*<<< orphan*/ * get () ; 
 int /*<<< orphan*/  is_keyword (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* make_label () ; 
 int /*<<< orphan*/ * make_vector () ; 
 int /*<<< orphan*/ * read_boolean_expr () ; 
 int /*<<< orphan*/ * read_stmt () ; 
 int /*<<< orphan*/  tok2s (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vec_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static Node *read_do_stmt() {
    char *beg = make_label();
    char *end = make_label();
    SET_JUMP_LABELS(beg, end);
    Node *body = read_stmt();
    RESTORE_JUMP_LABELS();
    Token *tok = get();
    if (!is_keyword(tok, KWHILE))
        errort(tok, "'while' is expected, but got %s", tok2s(tok));
    expect('(');
    Node *cond = read_boolean_expr();
    expect(')');
    expect(';');

    Vector *v = make_vector();
    vec_push(v, ast_dest(beg));
    if (body)
        vec_push(v, body);
    vec_push(v, ast_if(cond, ast_jump(beg), NULL));
    vec_push(v, ast_dest(end));
    return ast_compound_stmt(v);
}