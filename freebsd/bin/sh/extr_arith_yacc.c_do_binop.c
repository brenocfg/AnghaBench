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
typedef  int uintmax_t ;
typedef  int arith_t ;

/* Variables and functions */
#define  ARITH_ADD 143 
#define  ARITH_BAND 142 
#define  ARITH_BOR 141 
#define  ARITH_BXOR 140 
#define  ARITH_DIV 139 
#define  ARITH_EQ 138 
#define  ARITH_GE 137 
#define  ARITH_GT 136 
#define  ARITH_LE 135 
#define  ARITH_LSHIFT 134 
#define  ARITH_LT 133 
 int ARITH_MIN ; 
#define  ARITH_MUL 132 
#define  ARITH_NE 131 
#define  ARITH_REM 130 
#define  ARITH_RSHIFT 129 
#define  ARITH_SUB 128 
 int CHAR_BIT ; 
 int /*<<< orphan*/  yyerror (char*) ; 

__attribute__((used)) static arith_t do_binop(int op, arith_t a, arith_t b)
{

	switch (op) {
	default:
	case ARITH_REM:
	case ARITH_DIV:
		if (!b)
			yyerror("division by zero");
		if (a == ARITH_MIN && b == -1)
			yyerror("divide error");
		return op == ARITH_REM ? a % b : a / b;
	case ARITH_MUL:
		return (uintmax_t)a * (uintmax_t)b;
	case ARITH_ADD:
		return (uintmax_t)a + (uintmax_t)b;
	case ARITH_SUB:
		return (uintmax_t)a - (uintmax_t)b;
	case ARITH_LSHIFT:
		return (uintmax_t)a << (b & (sizeof(uintmax_t) * CHAR_BIT - 1));
	case ARITH_RSHIFT:
		return a >> (b & (sizeof(uintmax_t) * CHAR_BIT - 1));
	case ARITH_LT:
		return a < b;
	case ARITH_LE:
		return a <= b;
	case ARITH_GT:
		return a > b;
	case ARITH_GE:
		return a >= b;
	case ARITH_EQ:
		return a == b;
	case ARITH_NE:
		return a != b;
	case ARITH_BAND:
		return a & b;
	case ARITH_BXOR:
		return a ^ b;
	case ARITH_BOR:
		return a | b;
	}
}