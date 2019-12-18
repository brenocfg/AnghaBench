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
 int /*<<< orphan*/  CondPushBack (scalar_t__) ; 
 scalar_t__ CondT (int /*<<< orphan*/ ) ; 
 scalar_t__ CondToken (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ TOK_AND ; 
 scalar_t__ TOK_ERROR ; 
 scalar_t__ TOK_TRUE ; 

__attribute__((used)) static Token
CondF(Boolean doEval)
{
    Token   l, o;

    l = CondT(doEval);
    if (l != TOK_ERROR) {
	o = CondToken(doEval);

	if (o == TOK_AND) {
	    /*
	     * F -> T && F
	     *
	     * If T is TOK_FALSE, the whole thing will be TOK_FALSE, but we have to
	     * parse the r.h.s. anyway (to throw it away).
	     * If T is TOK_TRUE, the result is the r.h.s., be it an TOK_ERROR or no.
	     */
	    if (l == TOK_TRUE) {
		l = CondF(doEval);
	    } else {
		(void)CondF(FALSE);
	    }
	} else {
	    /*
	     * F -> T
	     */
	    CondPushBack(o);
	}
    }
    return (l);
}