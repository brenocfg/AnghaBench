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
typedef  int /*<<< orphan*/  uint32_t ;
struct proc {int p_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSBitAndAtomic (int /*<<< orphan*/ ,int*) ; 
 int P_PROFIL ; 

void
stopprofclock(struct proc *p)
{
	if (p->p_flag & P_PROFIL)
		OSBitAndAtomic(~((uint32_t)P_PROFIL), &p->p_flag);
}