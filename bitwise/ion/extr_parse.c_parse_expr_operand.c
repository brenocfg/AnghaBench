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
typedef  int /*<<< orphan*/  TokenSuffix ;
typedef  int /*<<< orphan*/  TokenMod ;
struct TYPE_2__ {unsigned long long int_val; char* start; char* end; double float_val; char* str_val; char* name; int /*<<< orphan*/  mod; int /*<<< orphan*/  suffix; int /*<<< orphan*/  pos; } ;
typedef  int /*<<< orphan*/  SrcPos ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  TOKEN_COLON ; 
 int /*<<< orphan*/  TOKEN_COMMA ; 
 int /*<<< orphan*/  TOKEN_FLOAT ; 
 int /*<<< orphan*/  TOKEN_INT ; 
 int /*<<< orphan*/  TOKEN_LBRACE ; 
 int /*<<< orphan*/  TOKEN_LPAREN ; 
 int /*<<< orphan*/  TOKEN_NAME ; 
 int /*<<< orphan*/  TOKEN_RPAREN ; 
 int /*<<< orphan*/  TOKEN_STR ; 
 int /*<<< orphan*/  alignof_keyword ; 
 int /*<<< orphan*/  expect_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal_error_here (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_token (int /*<<< orphan*/ ) ; 
 scalar_t__ match_keyword (int /*<<< orphan*/ ) ; 
 scalar_t__ match_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * new_expr_alignof_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * new_expr_alignof_type (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * new_expr_cast (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * new_expr_float (int /*<<< orphan*/ ,char const*,char const*,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * new_expr_int (int /*<<< orphan*/ ,unsigned long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * new_expr_name (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * new_expr_offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * new_expr_paren (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * new_expr_sizeof_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * new_expr_sizeof_type (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * new_expr_str (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * new_expr_typeof_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * new_expr_typeof_type (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  new_keyword ; 
 int /*<<< orphan*/ * new_typespec_name (int /*<<< orphan*/ ,char const**,int) ; 
 int /*<<< orphan*/  next_token () ; 
 int /*<<< orphan*/  offsetof_keyword ; 
 int /*<<< orphan*/ * parse_expr () ; 
 int /*<<< orphan*/ * parse_expr_compound (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * parse_expr_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_expr_unary () ; 
 char* parse_name () ; 
 int /*<<< orphan*/ * parse_type () ; 
 int /*<<< orphan*/  sizeof_keyword ; 
 TYPE_1__ token ; 
 int /*<<< orphan*/  token_info () ; 
 int /*<<< orphan*/  typeof_keyword ; 

Expr *parse_expr_operand(void) {
    SrcPos pos = token.pos;
    if (is_token(TOKEN_INT)) {
        unsigned long long val = token.int_val;
        TokenMod mod = token.mod;
        TokenSuffix suffix = token.suffix;
        next_token();
        return new_expr_int(pos, val, mod, suffix);
    } else if (is_token(TOKEN_FLOAT)) {
        const char *start = token.start;
        const char *end = token.end;
        double val = token.float_val;
        TokenSuffix suffix = token.suffix;
        next_token();
        return new_expr_float(pos, start, end, val, suffix);
    } else if (is_token(TOKEN_STR)) {
        const char *val = token.str_val;
        TokenMod mod = token.mod;
        next_token();
        return new_expr_str(pos, val, mod);
    } else if (is_token(TOKEN_NAME)) {
        const char *name = token.name;
        next_token();
        if (is_token(TOKEN_LBRACE)) {
            return parse_expr_compound(new_typespec_name(pos, &name, 1));
        } else {
            return new_expr_name(pos, name);
        }
    } else if (match_keyword(new_keyword)) {
        return parse_expr_new(pos);
    } else if (match_keyword(sizeof_keyword)) {
        expect_token(TOKEN_LPAREN);
        if (match_token(TOKEN_COLON)) {
            Typespec *type = parse_type();
            expect_token(TOKEN_RPAREN);
            return new_expr_sizeof_type(pos, type);
        } else {
            Expr *expr = parse_expr();
            expect_token(TOKEN_RPAREN);
            return new_expr_sizeof_expr(pos, expr);
        }
    } else if (match_keyword(alignof_keyword)) {
        expect_token(TOKEN_LPAREN);
        if (match_token(TOKEN_COLON)) {
            Typespec *type = parse_type();
            expect_token(TOKEN_RPAREN);
            return new_expr_alignof_type(pos, type);
        } else {
            Expr *expr = parse_expr();
            expect_token(TOKEN_RPAREN);
            return new_expr_alignof_expr(pos, expr);
        }
    } else if (match_keyword(typeof_keyword)) {
        expect_token(TOKEN_LPAREN);
        if (match_token(TOKEN_COLON)) {
            Typespec *type = parse_type();
            expect_token(TOKEN_RPAREN);
            return new_expr_typeof_type(pos, type);
        } else {
            Expr *expr = parse_expr();
            expect_token(TOKEN_RPAREN);
            return new_expr_typeof_expr(pos, expr);
        }
    } else if (match_keyword(offsetof_keyword)) {
        expect_token(TOKEN_LPAREN);
        Typespec *type = parse_type();
        expect_token(TOKEN_COMMA);
        const char *name = parse_name();
        expect_token(TOKEN_RPAREN);
        return new_expr_offsetof(pos, type, name);
    } else if (is_token(TOKEN_LBRACE)) {
        return parse_expr_compound(NULL);
    } else if (match_token(TOKEN_LPAREN)) {
        if (match_token(TOKEN_COLON)) {
            Typespec *type = parse_type();
            expect_token(TOKEN_RPAREN);
            if (is_token(TOKEN_LBRACE)) {
                return parse_expr_compound(type);
            } else {
                return new_expr_cast(pos, type, parse_expr_unary());
            }
        } else {
            Expr *expr = parse_expr();
            expect_token(TOKEN_RPAREN);
            return new_expr_paren(pos, expr);
        }
    } else {
        fatal_error_here("Unexpected token %s in expression", token_info());
        return NULL;
    }
}