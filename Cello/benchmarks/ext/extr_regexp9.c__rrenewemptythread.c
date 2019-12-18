#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* m; } ;
struct TYPE_9__ {int /*<<< orphan*/ * inst; TYPE_4__ se; } ;
struct TYPE_7__ {int /*<<< orphan*/ * rsp; } ;
struct TYPE_8__ {TYPE_1__ s; } ;
typedef  int /*<<< orphan*/  Rune ;
typedef  TYPE_3__ Relist ;
typedef  int /*<<< orphan*/  Reinst ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static Relist*
_rrenewemptythread(Relist *lp,	/* _relist to add to */
	Reinst *ip,		/* instruction to add */
	int ms,
	Rune *rsp)		/* pointers to subexpressions */
{
	Relist *p;

	for(p=lp; p->inst; p++){
		if(p->inst == ip){
			if(rsp < p->se.m[0].s.rsp) {
				if(ms > 1)
					memset(&p->se, 0, sizeof(p->se));
				p->se.m[0].s.rsp = rsp;
			}
			return 0;
		}
	}
	p->inst = ip;
	if(ms > 1)
		memset(&p->se, 0, sizeof(p->se));
	p->se.m[0].s.rsp = rsp;
	(++p)->inst = 0;
	return p;
}