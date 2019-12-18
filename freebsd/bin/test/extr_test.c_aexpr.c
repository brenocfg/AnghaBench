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
 scalar_t__ BAND ; 
 scalar_t__ nargc ; 
 int nexpr (int) ; 
 scalar_t__ t_lex (scalar_t__) ; 
 int /*<<< orphan*/ * t_wp ; 

__attribute__((used)) static int
aexpr(enum token n)
{
	int res;

	res = nexpr(n);
	if (t_lex(nargc > 0 ? (--nargc, *++t_wp) : NULL) == BAND)
		return aexpr(t_lex(nargc > 0 ? (--nargc, *++t_wp) : NULL)) &&
		    res;
	t_wp--;
	nargc++;
	return res;
}