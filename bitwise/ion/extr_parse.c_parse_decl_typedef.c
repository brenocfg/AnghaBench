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
typedef  int /*<<< orphan*/  Decl ;

/* Variables and functions */
 int /*<<< orphan*/  TOKEN_ASSIGN ; 
 int /*<<< orphan*/  TOKEN_SEMICOLON ; 
 int /*<<< orphan*/  expect_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * new_decl_typedef (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 char* parse_name () ; 
 int /*<<< orphan*/ * parse_type () ; 

Decl *parse_decl_typedef(SrcPos pos) {
    const char *name = parse_name();
    expect_token(TOKEN_ASSIGN);
    Typespec *type = parse_type();
    expect_token(TOKEN_SEMICOLON);
    return new_decl_typedef(pos, name, type);
}