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
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  pos; } ;
typedef  int /*<<< orphan*/  SrcPos ;

/* Variables and functions */
 int /*<<< orphan*/  TOKEN_DOT ; 
 int /*<<< orphan*/  TOKEN_LBRACE ; 
 int /*<<< orphan*/  TOKEN_LPAREN ; 
 int /*<<< orphan*/  TOKEN_NAME ; 
 int /*<<< orphan*/  TOKEN_RPAREN ; 
 int /*<<< orphan*/  buf_len (char const**) ; 
 int /*<<< orphan*/  buf_push (char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expect_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal_error_here (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  func_keyword ; 
 scalar_t__ is_token (int /*<<< orphan*/ ) ; 
 scalar_t__ match_keyword (int /*<<< orphan*/ ) ; 
 scalar_t__ match_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * new_typespec_name (int /*<<< orphan*/ ,char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next_token () ; 
 int /*<<< orphan*/  parse_name () ; 
 int /*<<< orphan*/ * parse_type () ; 
 int /*<<< orphan*/ * parse_type_func () ; 
 int /*<<< orphan*/ * parse_type_tuple () ; 
 TYPE_1__ token ; 
 int /*<<< orphan*/  token_info () ; 

Typespec *parse_type_base(void) {
    if (is_token(TOKEN_NAME)) {
        SrcPos pos = token.pos;
        const char **names = NULL;
        buf_push(names, token.name);
        next_token();
        while (match_token(TOKEN_DOT)) {
            buf_push(names, parse_name());
        }
        return new_typespec_name(pos, names, buf_len(names));
    } else if (match_keyword(func_keyword)) {
        return parse_type_func();
    } else if (match_token(TOKEN_LPAREN)) {
        Typespec *type = parse_type();
        expect_token(TOKEN_RPAREN);
        return type;
    } else if (match_token(TOKEN_LBRACE)) {
        return parse_type_tuple();
    } else {
        fatal_error_here("Unexpected token %s in type", token_info());
        return NULL;
    }
}