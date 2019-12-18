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
union yystype {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  sresult ;
typedef  int /*<<< orphan*/  arith_t ;

/* Variables and functions */
 int ARITH_ASS ; 
 int ARITH_ASS_MAX ; 
 int ARITH_ASS_MIN ; 
 char* ARITH_FORMAT_STR ; 
 int ARITH_VAR ; 
 int /*<<< orphan*/  DIGITS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arith_lookupvarint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cond (int,union yystype*,int,int) ; 
 int /*<<< orphan*/  do_binop (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setvar (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int yylex () ; 
 union yystype yylval ; 

__attribute__((used)) static arith_t assignment(int var, int noeval)
{
	union yystype val = yylval;
	int op = yylex();
	arith_t result;
	char sresult[DIGITS(result) + 1];

	if (var != ARITH_VAR)
		return cond(var, &val, op, noeval);

	if (op != ARITH_ASS && (op < ARITH_ASS_MIN || op >= ARITH_ASS_MAX))
		return cond(var, &val, op, noeval);

	result = assignment(yylex(), noeval);
	if (noeval)
		return result;

	if (op != ARITH_ASS)
		result = do_binop(op - 11, arith_lookupvarint(val.name), result);
	snprintf(sresult, sizeof(sresult), ARITH_FORMAT_STR, result);
	setvar(val.name, sresult, 0);
	return result;
}