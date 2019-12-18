#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Typespec ;
struct TYPE_5__ {scalar_t__ kind; char const* name; int /*<<< orphan*/  pos; } ;
typedef  int /*<<< orphan*/  Stmt ;
typedef  TYPE_1__ Expr ;

/* Variables and functions */
 scalar_t__ EXPR_NAME ; 
 int /*<<< orphan*/  TOKEN_ASSIGN ; 
 int /*<<< orphan*/  TOKEN_COLON ; 
 int /*<<< orphan*/  TOKEN_COLON_ASSIGN ; 
 int /*<<< orphan*/  fatal_error_here (char*) ; 
 int match_keyword (int /*<<< orphan*/ ) ; 
 scalar_t__ match_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * new_stmt_init (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 TYPE_1__* parse_expr () ; 
 int /*<<< orphan*/ * parse_type () ; 
 int /*<<< orphan*/  undef_keyword ; 

Stmt *parse_init_stmt(Expr *left) {
    if (match_token(TOKEN_COLON_ASSIGN)) {
        if (left->kind != EXPR_NAME) {
            fatal_error_here(":= must be preceded by a name");
            return NULL;
        }
        return new_stmt_init(left->pos, left->name, NULL, parse_expr(), false);
    } else if (match_token(TOKEN_COLON)) {
        if (left->kind != EXPR_NAME) {
            fatal_error_here(": must be preceded by a name");
            return NULL;
        }
        const char *name = left->name;
        Typespec *type = parse_type();
        Expr *expr = NULL;
        bool is_undef = false;
        if (match_token(TOKEN_ASSIGN)) {
            is_undef = match_keyword(undef_keyword);
            if (!is_undef) {
                expr = parse_expr();
            }
        }
        return new_stmt_init(left->pos, name, type, expr, is_undef);
    } else {
        return NULL;
    }
}