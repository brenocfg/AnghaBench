#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* processor_t ;
typedef  TYPE_2__* processor_set_t ;
struct TYPE_11__ {TYPE_1__* cpu_processor; } ;
struct TYPE_10__ {int (* pmChooseCPU ) (int,int,int) ;} ;
struct TYPE_9__ {int cpu_set_low; int cpu_set_hi; } ;
struct TYPE_8__ {int cpu_id; } ;

/* Variables and functions */
 TYPE_7__* cpu_datap (int) ; 
 TYPE_3__* pmDispatch ; 
 int /*<<< orphan*/  pmInitDone ; 
 int stub1 (int,int,int) ; 

processor_t
machine_choose_processor(processor_set_t pset,
			 processor_t preferred)
{
    int		startCPU;
    int		endCPU;
    int		preferredCPU;
    int		chosenCPU;

    if (!pmInitDone)
	return(preferred);

    if (pset == NULL) {
	startCPU = -1;
	endCPU = -1;
    } else {
	startCPU = pset->cpu_set_low;
	endCPU = pset->cpu_set_hi;
    }

    if (preferred == NULL)
	preferredCPU = -1;
    else
	preferredCPU = preferred->cpu_id;

    if (pmDispatch != NULL
	&& pmDispatch->pmChooseCPU != NULL) {
	chosenCPU = pmDispatch->pmChooseCPU(startCPU, endCPU, preferredCPU);

	if (chosenCPU == -1)
	    return(NULL);
	return(cpu_datap(chosenCPU)->cpu_processor);
    }

    return(preferred);
}