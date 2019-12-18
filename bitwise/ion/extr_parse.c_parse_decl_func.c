#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Typespec ;
struct TYPE_8__ {int is_incomplete; } ;
struct TYPE_7__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ StmtList ;
typedef  int /*<<< orphan*/  SrcPos ;
typedef  int /*<<< orphan*/  FuncParam ;
typedef  TYPE_2__ Decl ;

/* Variables and functions */
 int /*<<< orphan*/  TOKEN_COLON ; 
 int /*<<< orphan*/  TOKEN_COMMA ; 
 int /*<<< orphan*/  TOKEN_ELLIPSIS ; 
 int /*<<< orphan*/  TOKEN_LPAREN ; 
 int /*<<< orphan*/  TOKEN_RPAREN ; 
 int /*<<< orphan*/  TOKEN_SEMICOLON ; 
 int /*<<< orphan*/  buf_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buf_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error_here (char*) ; 
 int /*<<< orphan*/  expect_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_token (int /*<<< orphan*/ ) ; 
 scalar_t__ match_token (int /*<<< orphan*/ ) ; 
 TYPE_2__* new_decl_func (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,TYPE_1__) ; 
 int /*<<< orphan*/  parse_decl_func_param () ; 
 char* parse_name () ; 
 TYPE_1__ parse_stmt_block () ; 
 int /*<<< orphan*/ * parse_type () ; 

Decl *parse_decl_func(SrcPos pos) {
    const char *name = parse_name();
    expect_token(TOKEN_LPAREN);
    FuncParam *params = NULL;
    bool has_varargs = false;
    Typespec *varargs_type = NULL;
    if (!is_token(TOKEN_RPAREN)) {
        buf_push(params, parse_decl_func_param());
        while (match_token(TOKEN_COMMA)) {
            if (match_token(TOKEN_ELLIPSIS)) {
                if (has_varargs) {
                    error_here("Multiple ellipsis in function declaration");
                }
                if (!is_token(TOKEN_RPAREN)) {
                    varargs_type = parse_type();
                }
                has_varargs = true;
            } else {
                if (has_varargs) {
                    error_here("Ellipsis must be last parameter in function declaration");
                }
                buf_push(params, parse_decl_func_param());
            }
        }
    }
    expect_token(TOKEN_RPAREN);
    Typespec *ret_type = NULL;
    if (match_token(TOKEN_COLON)) {
        ret_type = parse_type();
    }
    StmtList block = {0};
    bool is_incomplete;
    if (match_token(TOKEN_SEMICOLON)) {
        is_incomplete = true;
    } else {
        block = parse_stmt_block();
        is_incomplete = false;
    }
    Decl *decl = new_decl_func(pos, name, params, buf_len(params), ret_type, has_varargs, varargs_type, block);
    decl->is_incomplete = is_incomplete;
    return decl;
}