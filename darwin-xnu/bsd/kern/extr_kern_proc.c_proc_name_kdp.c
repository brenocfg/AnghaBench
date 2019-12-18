#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  task_t ;
typedef  TYPE_1__* proc_t ;
struct TYPE_4__ {int /*<<< orphan*/ * p_comm; int /*<<< orphan*/ * p_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIN (int,int) ; 
 TYPE_1__* PROC_NULL ; 
 TYPE_1__* get_bsdtask_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
proc_name_kdp(task_t t, char * buf, int size)
{
	proc_t p = get_bsdtask_info(t);
	if (p == PROC_NULL)
		return;

	if ((size_t)size > sizeof(p->p_comm))
		strlcpy(buf, &p->p_name[0], MIN((int)sizeof(p->p_name), size));
	else
		strlcpy(buf, &p->p_comm[0], MIN((int)sizeof(p->p_comm), size));
}