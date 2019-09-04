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
struct st {int op; unsigned long r; } ;

/* Variables and functions */
 scalar_t__ binop (struct st*,int,unsigned long) ; 
 char* evalprim (struct st*,char const*,int) ; 
 char* parseop (struct st*,char const*) ; 

__attribute__((used)) static const char *evalbinop(struct st *st, const char *s, int minprec, int d)
{
	static const char prec[14] = {1,2,3,3,4,4,4,4,5,5,6,6,6,0};
	unsigned long left;
	int op;
	d--;
	s = evalprim(st, s, d);
	s = parseop(st, s);
	for (;;) {
		/*
		st->r (left hand side value) and st->op are now set,
		get the right hand side or back out if op has low prec,
		if op was missing then prec[op]==0
		*/
		op = st->op;
		if (prec[op] <= minprec)
			return s;
		left = st->r;
		s = evalbinop(st, s, prec[op], d);
		if (binop(st, op, left))
			return "";
	}
}