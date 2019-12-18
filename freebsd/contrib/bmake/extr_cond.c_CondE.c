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
 scalar_t__ CondF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CondPushBack (scalar_t__) ; 
 scalar_t__ CondToken (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ TOK_ERROR ; 
 scalar_t__ TOK_FALSE ; 
 scalar_t__ TOK_OR ; 

__attribute__((used)) static Token
CondE(Boolean doEval)
{
    Token   l, o;

    l = CondF(doEval);
    if (l != TOK_ERROR) {
	o = CondToken(doEval);

	if (o == TOK_OR) {
	    /*
	     * E -> F || E
	     *
	     * A similar thing occurs for ||, except that here we make sure
	     * the l.h.s. is TOK_FALSE before we bother to evaluate the r.h.s.
	     * Once again, if l is TOK_FALSE, the result is the r.h.s. and once
	     * again if l is TOK_TRUE, we parse the r.h.s. to throw it away.
	     */
	    if (l == TOK_FALSE) {
		l = CondE(doEval);
	    } else {
		(void)CondE(FALSE);
	    }
	} else {
	    /*
	     * E -> F
	     */
	    CondPushBack(o);
	}
    }
    return (l);
}