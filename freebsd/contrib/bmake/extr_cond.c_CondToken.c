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
typedef  scalar_t__ Token ;
typedef  int /*<<< orphan*/  Boolean ;

/* Variables and functions */
 scalar_t__ TOK_AND ; 
 scalar_t__ TOK_EOF ; 
 scalar_t__ TOK_LPAREN ; 
 scalar_t__ TOK_NONE ; 
 scalar_t__ TOK_NOT ; 
 scalar_t__ TOK_OR ; 
 scalar_t__ TOK_RPAREN ; 
 scalar_t__ compare_expression (int /*<<< orphan*/ ) ; 
 scalar_t__ compare_function (int /*<<< orphan*/ ) ; 
 char* condExpr ; 
 scalar_t__ condPushBack ; 

__attribute__((used)) static Token
CondToken(Boolean doEval)
{
    Token t;

    t = condPushBack;
    if (t != TOK_NONE) {
	condPushBack = TOK_NONE;
	return t;
    }

    while (*condExpr == ' ' || *condExpr == '\t') {
	condExpr++;
    }

    switch (*condExpr) {

    case '(':
	condExpr++;
	return TOK_LPAREN;

    case ')':
	condExpr++;
	return TOK_RPAREN;

    case '|':
	if (condExpr[1] == '|') {
	    condExpr++;
	}
	condExpr++;
	return TOK_OR;

    case '&':
	if (condExpr[1] == '&') {
	    condExpr++;
	}
	condExpr++;
	return TOK_AND;

    case '!':
	condExpr++;
	return TOK_NOT;

    case '#':
    case '\n':
    case '\0':
	return TOK_EOF;

    case '"':
    case '$':
	return compare_expression(doEval);

    default:
	return compare_function(doEval);
    }
}