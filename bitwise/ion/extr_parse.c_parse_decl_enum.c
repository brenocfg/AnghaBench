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
typedef  int /*<<< orphan*/  Typespec ;
typedef  int /*<<< orphan*/  SrcPos ;
typedef  int /*<<< orphan*/  EnumItem ;
typedef  int /*<<< orphan*/  Decl ;

/* Variables and functions */
 int /*<<< orphan*/  TOKEN_ASSIGN ; 
 int /*<<< orphan*/  TOKEN_COMMA ; 
 int /*<<< orphan*/  TOKEN_LBRACE ; 
 int /*<<< orphan*/  TOKEN_NAME ; 
 int /*<<< orphan*/  TOKEN_RBRACE ; 
 int /*<<< orphan*/  buf_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buf_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expect_token (int /*<<< orphan*/ ) ; 
 scalar_t__ is_token (int /*<<< orphan*/ ) ; 
 scalar_t__ match_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * new_decl_enum (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_decl_enum_item () ; 
 char* parse_name () ; 
 int /*<<< orphan*/ * parse_type () ; 

Decl *parse_decl_enum(SrcPos pos) {
    const char *name = NULL;
    if (is_token(TOKEN_NAME)) {
        name = parse_name();
    }
    Typespec *type = NULL;
    if (match_token(TOKEN_ASSIGN)) {
        type = parse_type();
    }
    expect_token(TOKEN_LBRACE);
    EnumItem *items = NULL;
    while (!is_token(TOKEN_RBRACE)) {
        buf_push(items, parse_decl_enum_item());
        if (!match_token(TOKEN_COMMA)) {
            break;
        }
    }
    expect_token(TOKEN_RBRACE);
    return new_decl_enum(pos, name, type, items, buf_len(items));
}