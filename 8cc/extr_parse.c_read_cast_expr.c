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
typedef  int /*<<< orphan*/  Type ;
typedef  int /*<<< orphan*/  Token ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  OP_CAST ; 
 int /*<<< orphan*/ * ast_uop (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expect (char) ; 
 int /*<<< orphan*/ * get () ; 
 scalar_t__ is_keyword (int /*<<< orphan*/ *,char) ; 
 scalar_t__ is_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * peek () ; 
 int /*<<< orphan*/ * read_cast_type () ; 
 int /*<<< orphan*/ * read_compound_literal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * read_postfix_expr_tail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * read_unary_expr () ; 
 int /*<<< orphan*/  unget_token (int /*<<< orphan*/ *) ; 

__attribute__((used)) static Node *read_cast_expr() {
    Token *tok = get();
    if (is_keyword(tok, '(') && is_type(peek())) {
        Type *ty = read_cast_type();
        expect(')');
        if (is_keyword(peek(), '{')) {
            Node *node = read_compound_literal(ty);
            return read_postfix_expr_tail(node);
        }
        return ast_uop(OP_CAST, ty, read_cast_expr());
    }
    unget_token(tok);
    return read_unary_expr();
}