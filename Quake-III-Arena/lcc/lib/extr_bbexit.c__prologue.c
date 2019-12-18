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
struct func {struct caller* callers; } ;
struct caller {scalar_t__ caller; int count; struct caller* link; } ;
struct _bbdata {struct _bbdata* link; } ;

/* Variables and functions */
 struct _bbdata* _bblist ; 
 scalar_t__ _caller ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bbexit ; 

void _prologue(struct func *callee, struct _bbdata *yylink) {
	static struct caller callers[4096];
	static int next;
	struct caller *p;

	if (!yylink->link) {
		yylink->link = _bblist;
		_bblist = yylink;
		if (next == 0)
			atexit(bbexit);
	}
	for (p = callee->callers; p; p = p->link)
		if (p->caller == _caller) {
			p->count++;
			break;
		}
	if (!p && next < sizeof callers/sizeof callers[0]) {
		p = &callers[next++];
		p->caller = _caller;
		p->count = 1;
		p->link = callee->callers;
		callee->callers = p;
	}
	_caller = 0;
}