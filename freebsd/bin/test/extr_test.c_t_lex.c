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
typedef  enum token { ____Placeholder_token } token ;

/* Variables and functions */
 scalar_t__ BUNOP ; 
 int EOI ; 
 int LPAREN ; 
 int OPERAND ; 
 int RPAREN ; 
 scalar_t__ TOKEN_TYPE (int) ; 
 scalar_t__ UNOP ; 
 int find_op (char*) ; 
 scalar_t__ islparenoperand () ; 
 scalar_t__ isrparenoperand () ; 
 scalar_t__ isunopoperand () ; 

__attribute__((used)) static enum token
t_lex(char *s)
{
	int num;

	if (s == NULL) {
		return EOI;
	}
	num = find_op(s);
	if (((TOKEN_TYPE(num) == UNOP || TOKEN_TYPE(num) == BUNOP)
				&& isunopoperand()) ||
	    (num == LPAREN && islparenoperand()) ||
	    (num == RPAREN && isrparenoperand()))
		return OPERAND;
	return num;
}