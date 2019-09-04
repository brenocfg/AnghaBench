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
struct proc {int p_csflags; } ;

/* Variables and functions */
 int CS_ENFORCEMENT ; 
 scalar_t__ cs_process_enforcement_enable ; 
 struct proc* current_proc () ; 

int
cs_process_enforcement(struct proc *p)
{

	if (cs_process_enforcement_enable)
		return 1;
	
	if (p == NULL)
		p = current_proc();

	if (p != NULL && (p->p_csflags & CS_ENFORCEMENT))
		return 1;

	return 0;
}