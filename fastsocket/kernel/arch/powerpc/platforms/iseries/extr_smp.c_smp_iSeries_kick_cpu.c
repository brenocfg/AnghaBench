#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int dyn_proc_status; } ;
struct TYPE_3__ {int cpu_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int NR_CPUS ; 
 TYPE_2__* lppaca ; 
 TYPE_1__* paca ; 

__attribute__((used)) static void smp_iSeries_kick_cpu(int nr)
{
	BUG_ON((nr < 0) || (nr >= NR_CPUS));

	/* Verify that our partition has a processor nr */
	if (lppaca[nr].dyn_proc_status >= 2)
		return;

	/* The processor is currently spinning, waiting
	 * for the cpu_start field to become non-zero
	 * After we set cpu_start, the processor will
	 * continue on to secondary_start in iSeries_head.S
	 */
	paca[nr].cpu_start = 1;
}