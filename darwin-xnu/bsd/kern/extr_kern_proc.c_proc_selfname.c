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
struct TYPE_3__ {int /*<<< orphan*/ * p_comm; } ;

/* Variables and functions */
 TYPE_1__* current_proc () ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ *,int) ; 

void
proc_selfname(char * buf, int  size)
{
	proc_t p;

	if ((p = current_proc())!= (proc_t)0) {
		strlcpy(buf, &p->p_comm[0], size);
	}
}