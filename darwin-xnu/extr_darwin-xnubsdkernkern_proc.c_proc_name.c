#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* proc_t ;
struct TYPE_5__ {int /*<<< orphan*/ * p_comm; } ;

/* Variables and functions */
 TYPE_1__* PROC_NULL ; 
 TYPE_1__* proc_find (int) ; 
 int /*<<< orphan*/  proc_rele (TYPE_1__*) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ *,int) ; 

void
proc_name(int pid, char * buf, int size)
{
	proc_t p;

	if ((p = proc_find(pid)) != PROC_NULL) {
		strlcpy(buf, &p->p_comm[0], size);
		proc_rele(p);
	}
}