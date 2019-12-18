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
typedef  int Token ;
struct TYPE_2__ {int /*<<< orphan*/  doNot; int /*<<< orphan*/  (* defProc ) (int /*<<< orphan*/ ,char*) ;int /*<<< orphan*/ * form; } ;
typedef  void* Boolean ;

/* Variables and functions */
 int /*<<< orphan*/  COND ; 
 scalar_t__ CondCvtArg (char*,double*) ; 
 char* CondGetString (void*,void**,void**,void*) ; 
 scalar_t__ DEBUG (int /*<<< orphan*/ ) ; 
 void* FALSE ; 
 int /*<<< orphan*/  PARSE_WARNING ; 
 int /*<<< orphan*/  Parse_Error (int /*<<< orphan*/ ,char*) ; 
 int TOK_ERROR ; 
 int TOK_FALSE ; 
 int* condExpr ; 
 int /*<<< orphan*/  debug_file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (void*) ; 
 TYPE_1__* if_info ; 
 scalar_t__ isspace (unsigned char) ; 
 void* lhsStrict ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static Token
compare_expression(Boolean doEval)
{
    Token	t;
    char	*lhs;
    char	*rhs;
    char	*op;
    void	*lhsFree;
    void	*rhsFree;
    Boolean lhsQuoted;
    Boolean rhsQuoted;
    double  	left, right;

    t = TOK_ERROR;
    rhs = NULL;
    lhsFree = rhsFree = FALSE;
    lhsQuoted = rhsQuoted = FALSE;
    
    /*
     * Parse the variable spec and skip over it, saving its
     * value in lhs.
     */
    lhs = CondGetString(doEval, &lhsQuoted, &lhsFree, lhsStrict);
    if (!lhs)
	goto done;

    /*
     * Skip whitespace to get to the operator
     */
    while (isspace((unsigned char) *condExpr))
	condExpr++;

    /*
     * Make sure the operator is a valid one. If it isn't a
     * known relational operator, pretend we got a
     * != 0 comparison.
     */
    op = condExpr;
    switch (*condExpr) {
	case '!':
	case '=':
	case '<':
	case '>':
	    if (condExpr[1] == '=') {
		condExpr += 2;
	    } else {
		condExpr += 1;
	    }
	    break;
	default:
	    if (!doEval) {
		t = TOK_FALSE;
		goto done;
	    }
	    /* For .ifxxx "..." check for non-empty string. */
	    if (lhsQuoted) {
		t = lhs[0] != 0;
		goto done;
	    }
	    /* For .ifxxx <number> compare against zero */
	    if (CondCvtArg(lhs, &left)) { 
		t = left != 0.0;
		goto done;
	    }
	    /* For .if ${...} check for non-empty string (defProc is ifdef). */
	    if (if_info->form[0] == 0) {
		t = lhs[0] != 0;
		goto done;
	    }
	    /* Otherwise action default test ... */
	    t = if_info->defProc(strlen(lhs), lhs) != if_info->doNot;
	    goto done;
    }

    while (isspace((unsigned char)*condExpr))
	condExpr++;

    if (*condExpr == '\0') {
	Parse_Error(PARSE_WARNING,
		    "Missing right-hand-side of operator");
	goto done;
    }

    rhs = CondGetString(doEval, &rhsQuoted, &rhsFree, FALSE);
    if (!rhs)
	goto done;

    if (rhsQuoted || lhsQuoted) {
do_string_compare:
	if (((*op != '!') && (*op != '=')) || (op[1] != '=')) {
	    Parse_Error(PARSE_WARNING,
    "String comparison operator should be either == or !=");
	    goto done;
	}

	if (DEBUG(COND)) {
	    fprintf(debug_file, "lhs = \"%s\", rhs = \"%s\", op = %.2s\n",
		   lhs, rhs, op);
	}
	/*
	 * Null-terminate rhs and perform the comparison.
	 * t is set to the result.
	 */
	if (*op == '=') {
	    t = strcmp(lhs, rhs) == 0;
	} else {
	    t = strcmp(lhs, rhs) != 0;
	}
    } else {
	/*
	 * rhs is either a float or an integer. Convert both the
	 * lhs and the rhs to a double and compare the two.
	 */
    
	if (!CondCvtArg(lhs, &left) || !CondCvtArg(rhs, &right))
	    goto do_string_compare;

	if (DEBUG(COND)) {
	    fprintf(debug_file, "left = %f, right = %f, op = %.2s\n", left,
		   right, op);
	}
	switch(op[0]) {
	case '!':
	    if (op[1] != '=') {
		Parse_Error(PARSE_WARNING,
			    "Unknown operator");
		goto done;
	    }
	    t = (left != right);
	    break;
	case '=':
	    if (op[1] != '=') {
		Parse_Error(PARSE_WARNING,
			    "Unknown operator");
		goto done;
	    }
	    t = (left == right);
	    break;
	case '<':
	    if (op[1] == '=') {
		t = (left <= right);
	    } else {
		t = (left < right);
	    }
	    break;
	case '>':
	    if (op[1] == '=') {
		t = (left >= right);
	    } else {
		t = (left > right);
	    }
	    break;
	}
    }

done:
    free(lhsFree);
    free(rhsFree);
    return t;
}