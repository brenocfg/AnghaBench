#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TokenKind ;
struct TYPE_2__ {char* name; int /*<<< orphan*/  kind; int /*<<< orphan*/  pos; } ;
typedef  int /*<<< orphan*/  SrcPos ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  TOKEN_COMMA ; 
 int /*<<< orphan*/  TOKEN_DEC ; 
 int /*<<< orphan*/  TOKEN_DOT ; 
 int /*<<< orphan*/  TOKEN_INC ; 
 int /*<<< orphan*/  TOKEN_LBRACKET ; 
 int /*<<< orphan*/  TOKEN_LPAREN ; 
 int /*<<< orphan*/  TOKEN_NAME ; 
 int /*<<< orphan*/  TOKEN_RBRACKET ; 
 int /*<<< orphan*/  TOKEN_RPAREN ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  buf_len (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  buf_push (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expect_token (int /*<<< orphan*/ ) ; 
 scalar_t__ is_token (int /*<<< orphan*/ ) ; 
 scalar_t__ match_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * new_expr_call (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * new_expr_field (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * new_expr_index (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * new_expr_modify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next_token () ; 
 int /*<<< orphan*/ * parse_expr () ; 
 int /*<<< orphan*/ * parse_expr_operand () ; 
 TYPE_1__ token ; 

Expr *parse_expr_base(void) {
    Expr *expr = parse_expr_operand();
    while (is_token(TOKEN_LPAREN) || is_token(TOKEN_LBRACKET) || is_token(TOKEN_DOT) || is_token(TOKEN_INC) || is_token(TOKEN_DEC)) {
        SrcPos pos = token.pos;
        if (match_token(TOKEN_LPAREN)) {
            Expr **args = NULL;
            if (!is_token(TOKEN_RPAREN)) {
                buf_push(args, parse_expr());
                while (match_token(TOKEN_COMMA)) {
                    buf_push(args, parse_expr());
                }
            }
            expect_token(TOKEN_RPAREN);
            expr = new_expr_call(pos, expr, args, buf_len(args));
        } else if (match_token(TOKEN_LBRACKET)) {
            Expr *index = parse_expr();
            expect_token(TOKEN_RBRACKET);
            expr = new_expr_index(pos, expr, index);
        } else if (is_token(TOKEN_DOT)) {
            next_token();
            const char *field = token.name;
            expect_token(TOKEN_NAME);
            expr = new_expr_field(pos, expr, field);
        } else {
            assert(is_token(TOKEN_INC) || is_token(TOKEN_DEC));
            TokenKind op = token.kind;
            next_token();
            expr = new_expr_modify(pos, op, true, expr);
        }
    }
    return expr;
}