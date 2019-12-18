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
typedef  int /*<<< orphan*/  Typespec ;
struct TYPE_2__ {int /*<<< orphan*/  pos; } ;
typedef  int /*<<< orphan*/  SrcPos ;
typedef  int /*<<< orphan*/  Expr ;
typedef  int /*<<< orphan*/  CompoundField ;

/* Variables and functions */
 int /*<<< orphan*/  TOKEN_COMMA ; 
 int /*<<< orphan*/  TOKEN_LBRACE ; 
 int /*<<< orphan*/  TOKEN_RBRACE ; 
 int /*<<< orphan*/  buf_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buf_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expect_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  match_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * new_expr_compound (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_expr_compound_field () ; 
 TYPE_1__ token ; 

Expr *parse_expr_compound(Typespec *type) {
    SrcPos pos = token.pos;
    expect_token(TOKEN_LBRACE);
    CompoundField *fields = NULL;
    while (!is_token(TOKEN_RBRACE)) {
        buf_push(fields, parse_expr_compound_field());
        if (!match_token(TOKEN_COMMA)) {
            break;
        }
    }
    expect_token(TOKEN_RBRACE);
    return new_expr_compound(pos, type, fields, buf_len(fields));
}