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
struct st {unsigned long n; unsigned long r; } ;

/* Variables and functions */
 char* evalexpr (struct st*,char const*,int) ; 

unsigned long __pleval(const char *s, unsigned long n)
{
	struct st st;
	st.n = n;
	s = evalexpr(&st, s, 100);
	return *s == ';' ? st.r : -1;
}