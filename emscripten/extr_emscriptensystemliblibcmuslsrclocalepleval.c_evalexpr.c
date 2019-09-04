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
struct st {unsigned long r; } ;

/* Variables and functions */
 char* evalbinop (struct st*,char const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static const char *evalexpr(struct st *st, const char *s, int d)
{
	unsigned long a, b;
	if (--d < 0)
		return "";
	s = evalbinop(st, s, 0, d);
	if (*s != '?')
		return s;
	a = st->r;
	s = evalexpr(st, s+1, d);
	if (*s != ':')
		return "";
	b = st->r;
	s = evalexpr(st, s+1, d);
	st->r = a ? b : st->r;
	return s;
}