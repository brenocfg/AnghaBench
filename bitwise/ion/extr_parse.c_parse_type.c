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

/* Variables and functions */
 int /*<<< orphan*/  TOKEN_LBRACKET ; 
 int /*<<< orphan*/  TOKEN_MUL ; 
 int /*<<< orphan*/  TOKEN_RBRACKET ; 
 int /*<<< orphan*/  assert (scalar_t__) ; 
 int /*<<< orphan*/  const_keyword ; 
 int /*<<< orphan*/  expect_token (int /*<<< orphan*/ ) ; 
 scalar_t__ is_keyword (int /*<<< orphan*/ ) ; 
 scalar_t__ is_token (int /*<<< orphan*/ ) ; 
 scalar_t__ match_keyword (int /*<<< orphan*/ ) ; 
 scalar_t__ match_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * new_typespec_array (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * new_typespec_const (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * new_typespec_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next_token () ; 
 int /*<<< orphan*/ * parse_expr () ; 
 int /*<<< orphan*/ * parse_type_base () ; 
 TYPE_1__ token ; 

Typespec *parse_type(void) {
    Typespec *type = parse_type_base();
    SrcPos pos = token.pos;
    while (is_token(TOKEN_LBRACKET) || is_token(TOKEN_MUL) || is_keyword(const_keyword)) {
        if (match_token(TOKEN_LBRACKET)) {
            Expr *size = NULL;
            if (!is_token(TOKEN_RBRACKET)) {
                size = parse_expr();
            }
            expect_token(TOKEN_RBRACKET);
            type = new_typespec_array(pos, type, size);
        } else if (match_keyword(const_keyword)) {
            type = new_typespec_const(pos, type);
        } else {
            assert(is_token(TOKEN_MUL));
            next_token();
            type = new_typespec_ptr(pos, type);
        }
    }
    return type;
}