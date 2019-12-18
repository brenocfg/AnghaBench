#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* proc_t ;
struct TYPE_3__ {scalar_t__ p_childrencnt; int p_listflag; } ;

/* Variables and functions */
 int P_LIST_CHILDDRAINED ; 
 int P_LIST_CHILDDRWAIT ; 
 int P_LIST_CHILDLKWAIT ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  wakeup (scalar_t__*) ; 

void
proc_childdrainend(proc_t p)
{
#if __PROC_INTERNAL_DEBUG
	if (p->p_childrencnt > 0)
		panic("exiting: children stil hanging around\n");
#endif
	p->p_listflag |= P_LIST_CHILDDRAINED;
	if ((p->p_listflag & (P_LIST_CHILDLKWAIT |P_LIST_CHILDDRWAIT)) != 0) {
		p->p_listflag &= ~(P_LIST_CHILDLKWAIT |P_LIST_CHILDDRWAIT);
		wakeup(&p->p_childrencnt);
	}
}