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

/* Variables and functions */
 unsigned short IOPRIO_CLASS_BE ; 
 unsigned short IOPRIO_CLASS_NONE ; 
 unsigned short IOPRIO_PRIO_CLASS (unsigned short) ; 
 int min (unsigned short,unsigned short) ; 

int ioprio_best(unsigned short aprio, unsigned short bprio)
{
	unsigned short aclass = IOPRIO_PRIO_CLASS(aprio);
	unsigned short bclass = IOPRIO_PRIO_CLASS(bprio);

	if (aclass == IOPRIO_CLASS_NONE)
		aclass = IOPRIO_CLASS_BE;
	if (bclass == IOPRIO_CLASS_NONE)
		bclass = IOPRIO_CLASS_BE;

	if (aclass == bclass)
		return min(aprio, bprio);
	if (aclass > bclass)
		return bprio;
	else
		return aprio;
}