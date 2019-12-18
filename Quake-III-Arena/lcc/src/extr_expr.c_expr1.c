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
typedef  void* Tree ;

/* Variables and functions */
 scalar_t__ ASGN ; 
#define  ID 129 
#define  IF 128 
 void* asgntree (scalar_t__,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expect (char) ; 
 void* expr2 () ; 
 char gettok () ; 
 void* incr (int,void*,void*) ; 
 scalar_t__* oper ; 
 int* prec ; 
 char t ; 
 int /*<<< orphan*/  test (int,char*) ; 
 int /*<<< orphan*/  value (void*) ; 

Tree expr1(int tok) {
	static char stop[] = { IF, ID, 0 };
	Tree p = expr2();

	if (t == '='
	|| (prec[t] >=  6 && prec[t] <=  8)
	|| (prec[t] >= 11 && prec[t] <= 13)) {
		int op = t;
		t = gettok();
		if (oper[op] == ASGN)
			p = asgntree(ASGN, p, value(expr1(0)));
		else
			{
				expect('=');
				p = incr(op, p, expr1(0));
			}
	}
	if (tok)	
		test(tok, stop);
	return p;
}