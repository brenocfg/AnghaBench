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
typedef  union yystype {int dummy; } yystype ;
typedef  int /*<<< orphan*/  arith_t ;

/* Variables and functions */
 int ARITH_BINOP_MAX ; 
 int ARITH_BINOP_MIN ; 
 int arith_prec (int) ; 
 int /*<<< orphan*/  do_binop (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ higher_prec (int,int) ; 
 int last_token ; 
 int /*<<< orphan*/  primary (int,union yystype*,int,int) ; 
 int yylex () ; 
 union yystype yylval ; 

__attribute__((used)) static arith_t binop2(arith_t a, int op, int precedence, int noeval)
{
	for (;;) {
		union yystype val;
		arith_t b;
		int op2;
		int token;

		token = yylex();
		val = yylval;

		b = primary(token, &val, yylex(), noeval);

		op2 = last_token;
		if (op2 >= ARITH_BINOP_MIN && op2 < ARITH_BINOP_MAX &&
		    higher_prec(op2, op)) {
			b = binop2(b, op2, arith_prec(op), noeval);
			op2 = last_token;
		}

		a = noeval ? b : do_binop(op, a, b);

		if (op2 < ARITH_BINOP_MIN || op2 >= ARITH_BINOP_MAX ||
		    arith_prec(op2) >= precedence)
			return a;

		op = op2;
	}
}