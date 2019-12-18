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

/* Variables and functions */
 int /*<<< orphan*/  TOKEN_COLON ; 
 int /*<<< orphan*/  TOKEN_COMMA ; 
 int /*<<< orphan*/  TOKEN_ELLIPSIS ; 
 int /*<<< orphan*/  TOKEN_LPAREN ; 
 int /*<<< orphan*/  TOKEN_RPAREN ; 
 int /*<<< orphan*/  buf_len (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  buf_push (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error_here (char*) ; 
 int /*<<< orphan*/  expect_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_token (int /*<<< orphan*/ ) ; 
 scalar_t__ match_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * new_typespec_func (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * parse_type () ; 
 int /*<<< orphan*/  parse_type_func_param () ; 
 TYPE_1__ token ; 

Typespec *parse_type_func(void) {
    SrcPos pos = token.pos;
    Typespec **args = NULL;
    bool has_varargs = false;
    expect_token(TOKEN_LPAREN);
    if (!is_token(TOKEN_RPAREN)) {
        buf_push(args, parse_type_func_param());
        while (match_token(TOKEN_COMMA)) {
            if (match_token(TOKEN_ELLIPSIS)) {
                if (has_varargs) {
                    error_here("Multiple ellipsis instances in function type");
                }
                has_varargs = true;
            } else {
                if (has_varargs) {
                    error_here("Ellipsis must be last parameter in function type");
                }
                buf_push(args, parse_type_func_param());
            }
        }
    }
    expect_token(TOKEN_RPAREN);
    Typespec *ret = NULL;
    if (match_token(TOKEN_COLON)) {
        ret = parse_type();
    }
    return new_typespec_func(pos, args, buf_len(args), ret, has_varargs);
}