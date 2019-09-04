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
struct st {int r; int n; } ;

/* Variables and functions */
 char* evalexpr (struct st*,char const*,int) ; 
 scalar_t__ isdigit (char const) ; 
 char const* skipspace (char const*) ; 
 int strtoul (char const*,char**,int) ; 

__attribute__((used)) static const char *evalprim(struct st *st, const char *s, int d)
{
	char *e;
	if (--d < 0) return "";
	s = skipspace(s);
	if (isdigit(*s)) {
		st->r = strtoul(s, &e, 10);
		if (e == s || st->r == -1) return "";
		return skipspace(e);
	}
	if (*s == 'n') {
		st->r = st->n;
		return skipspace(s+1);
	}
	if (*s == '(') {
		s = evalexpr(st, s+1, d);
		if (*s != ')') return "";
		return skipspace(s+1);
	}
	if (*s == '!') {
		s = evalprim(st, s+1, d);
		st->r = !st->r;
		return s;
	}
	return "";
}