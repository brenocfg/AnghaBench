#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ prec; int /*<<< orphan*/  assoc; } ;
typedef  TYPE_1__ bucket ;

/* Variables and functions */
 int /*<<< orphan*/  IS_IDENT (int) ; 
 scalar_t__ UNDEFINED ; 
 int* cptr ; 
 TYPE_1__* get_literal () ; 
 TYPE_1__* get_name () ; 
 scalar_t__ isalpha (int) ; 
 int /*<<< orphan*/  line ; 
 int /*<<< orphan*/  lineno ; 
 int nextc () ; 
 size_t nrules ; 
 int /*<<< orphan*/  prec_redeclared () ; 
 int /*<<< orphan*/ * rassoc ; 
 scalar_t__* rprec ; 
 int /*<<< orphan*/  syntax_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
mark_symbol(void)
{
    int c;
    bucket *bp = NULL;

    c = cptr[1];
    if (c == '%' || c == '\\')
    {
	cptr += 2;
	return (1);
    }

    if (c == '=')
	cptr += 2;
    else if ((c == 'p' || c == 'P') &&
	     ((c = cptr[2]) == 'r' || c == 'R') &&
	     ((c = cptr[3]) == 'e' || c == 'E') &&
	     ((c = cptr[4]) == 'c' || c == 'C') &&
	     ((c = cptr[5], !IS_IDENT(c))))
	cptr += 5;
    else
	syntax_error(lineno, line, cptr);

    c = nextc();
    if (isalpha(c) || c == '_' || c == '.' || c == '$')
	bp = get_name();
    else if (c == '\'' || c == '"')
	bp = get_literal();
    else
    {
	syntax_error(lineno, line, cptr);
	/*NOTREACHED */
    }

    if (rprec[nrules] != UNDEFINED && bp->prec != rprec[nrules])
	prec_redeclared();

    rprec[nrules] = bp->prec;
    rassoc[nrules] = bp->assoc;
    return (0);
}