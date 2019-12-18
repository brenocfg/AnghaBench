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
struct TYPE_3__ {int p_listflag; scalar_t__ p_parentref; } ;

/* Variables and functions */
 int P_LIST_CHILDDRSTART ; 
 int P_LIST_PARENTREFWAIT ; 
 int /*<<< orphan*/  msleep (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  proc_list_mlock ; 

void
proc_childdrainstart(proc_t p)
{
#if __PROC_INTERNAL_DEBUG
	if ((p->p_listflag & P_LIST_CHILDDRSTART) == P_LIST_CHILDDRSTART)
		panic("proc_childdrainstart: childdrain already started\n");
#endif
	p->p_listflag |= P_LIST_CHILDDRSTART;
	/* wait for all that hold parentrefs to drop */
	while (p->p_parentref > 0) {
		p->p_listflag |= P_LIST_PARENTREFWAIT;
		msleep(&p->p_parentref, proc_list_mlock, 0, "proc_childdrainstart", 0) ;
	}
}