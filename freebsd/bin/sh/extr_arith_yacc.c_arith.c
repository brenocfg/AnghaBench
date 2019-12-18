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
struct stackmark {int dummy; } ;
typedef  int /*<<< orphan*/  arith_t ;

/* Variables and functions */
 char const* arith_buf ; 
 char const* arith_startbuf ; 
 int /*<<< orphan*/  assignment (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ last_token ; 
 int /*<<< orphan*/  popstackmark (struct stackmark*) ; 
 int /*<<< orphan*/  setstackmark (struct stackmark*) ; 
 int /*<<< orphan*/  yyerror (char*) ; 
 int /*<<< orphan*/  yylex () ; 

arith_t arith(const char *s)
{
	struct stackmark smark;
	arith_t result;

	setstackmark(&smark);

	arith_buf = arith_startbuf = s;

	result = assignment(yylex(), 0);

	if (last_token)
		yyerror("expecting EOF");

	popstackmark(&smark);

	return result;
}