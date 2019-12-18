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

/* Variables and functions */
 scalar_t__ BINOP ; 
 scalar_t__ TOKEN_TYPE (int) ; 
 int find_op (char*) ; 
 int nargc ; 
 int parenlevel ; 
 scalar_t__ strcmp (char*,char*) ; 
 char** t_wp ; 

__attribute__((used)) static int
isunopoperand(void)
{
	char *s;
	char *t;
	int num;

	if (nargc == 1)
		return 1;
	s = *(t_wp + 1);
	if (nargc == 2)
		return parenlevel == 1 && strcmp(s, ")") == 0;
	t = *(t_wp + 2);
	num = find_op(s);
	return TOKEN_TYPE(num) == BINOP &&
	    (parenlevel == 0 || t[0] != ')' || t[1] != '\0');
}