#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* proc_t ;
typedef  scalar_t__ pid_t ;
struct TYPE_10__ {TYPE_2__* lh_first; } ;
struct TYPE_8__ {TYPE_2__* le_next; } ;
struct TYPE_9__ {scalar_t__ p_pid; TYPE_1__ p_hash; } ;

/* Variables and functions */
 TYPE_7__* PIDHASH (scalar_t__) ; 
 TYPE_2__* kernproc ; 
 int /*<<< orphan*/  panic (char*,TYPE_2__*,TYPE_2__*,scalar_t__,scalar_t__) ; 

proc_t
pfind_locked(pid_t pid)
{
	proc_t p;
#if DEBUG
	proc_t q;
#endif

	if (!pid)
		return (kernproc);

	for (p = PIDHASH(pid)->lh_first; p != 0; p = p->p_hash.le_next) {
		if (p->p_pid == pid) {
#if DEBUG
			for (q = p->p_hash.le_next; q != 0; q = q->p_hash.le_next) {
				if ((p !=q) && (q->p_pid == pid))	
					panic("two procs with same pid %p:%p:%d:%d\n", p, q, p->p_pid, q->p_pid);
			}
#endif
			return (p);
		}
	}
	return (NULL);
}