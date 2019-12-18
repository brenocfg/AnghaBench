#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t pgprocno; } ;
struct TYPE_5__ {int* procAdded; scalar_t__ procCount; TYPE_2__** procs; } ;
typedef  TYPE_1__ PROCStack ;
typedef  TYPE_2__ PGPROC ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ TotalProcCount () ; 

__attribute__((used)) static void
AddProcToVisit(PROCStack *remaining, PGPROC *proc)
{
	if (remaining->procAdded[proc->pgprocno])
	{
		return;
	}

	Assert(remaining->procCount < TotalProcCount());

	remaining->procs[remaining->procCount++] = proc;
	remaining->procAdded[proc->pgprocno] = true;
}