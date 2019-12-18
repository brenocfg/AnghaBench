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
typedef  int /*<<< orphan*/  Boolean ;

/* Variables and functions */
 int COND_INVALID ; 
 int COND_PARSE ; 
 int CondE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CondToken (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TOK_EOF ; 
#define  TOK_ERROR 130 
#define  TOK_FALSE 129 
#define  TOK_TRUE 128 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static int
do_Cond_EvalExpression(Boolean *value)
{

    switch (CondE(TRUE)) {
    case TOK_TRUE:
	if (CondToken(TRUE) == TOK_EOF) {
	    *value = TRUE;
	    return COND_PARSE;
	}
	break;
    case TOK_FALSE:
	if (CondToken(TRUE) == TOK_EOF) {
	    *value = FALSE;
	    return COND_PARSE;
	}
	break;
    default:
    case TOK_ERROR:
	break;
    }

    return COND_INVALID;
}