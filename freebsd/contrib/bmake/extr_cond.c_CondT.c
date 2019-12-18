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
 scalar_t__ CondE (int /*<<< orphan*/ ) ; 
 scalar_t__ CondToken (int /*<<< orphan*/ ) ; 
 scalar_t__ TOK_EOF ; 
 scalar_t__ TOK_ERROR ; 
 scalar_t__ TOK_FALSE ; 
 scalar_t__ TOK_LPAREN ; 
 scalar_t__ TOK_NOT ; 
 scalar_t__ TOK_RPAREN ; 
 scalar_t__ TOK_TRUE ; 

__attribute__((used)) static Token
CondT(Boolean doEval)
{
    Token   t;

    t = CondToken(doEval);

    if (t == TOK_EOF) {
	/*
	 * If we reached the end of the expression, the expression
	 * is malformed...
	 */
	t = TOK_ERROR;
    } else if (t == TOK_LPAREN) {
	/*
	 * T -> ( E )
	 */
	t = CondE(doEval);
	if (t != TOK_ERROR) {
	    if (CondToken(doEval) != TOK_RPAREN) {
		t = TOK_ERROR;
	    }
	}
    } else if (t == TOK_NOT) {
	t = CondT(doEval);
	if (t == TOK_TRUE) {
	    t = TOK_FALSE;
	} else if (t == TOK_FALSE) {
	    t = TOK_TRUE;
	}
    }
    return (t);
}