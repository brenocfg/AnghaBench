#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_4__* allPgXact; } ;
struct TYPE_10__ {scalar_t__ locktag_type; } ;
struct TYPE_14__ {TYPE_2__ tag; } ;
struct TYPE_13__ {scalar_t__ waitStatus; size_t pgprocno; TYPE_3__* waitProcLock; } ;
struct TYPE_12__ {int vacuumFlags; } ;
struct TYPE_9__ {TYPE_6__* myLock; } ;
struct TYPE_11__ {TYPE_1__ tag; } ;
typedef  TYPE_3__ PROCLOCK ;
typedef  TYPE_4__ PGXACT ;
typedef  TYPE_5__ PGPROC ;
typedef  TYPE_6__ LOCK ;

/* Variables and functions */
 scalar_t__ LOCKTAG_PAGE ; 
 scalar_t__ LOCKTAG_RELATION_EXTEND ; 
 scalar_t__ LOCKTAG_SPECULATIVE_TOKEN ; 
 int PROC_IS_AUTOVACUUM ; 
 TYPE_7__* ProcGlobal ; 
 scalar_t__ STATUS_WAITING ; 

__attribute__((used)) static bool
IsProcessWaitingForSafeOperations(PGPROC *proc)
{
	PROCLOCK *waitProcLock = NULL;
	LOCK *waitLock = NULL;
	PGXACT *pgxact = NULL;

	if (proc->waitStatus != STATUS_WAITING)
	{
		return false;
	}

	/* get the transaction that the backend associated with */
	pgxact = &ProcGlobal->allPgXact[proc->pgprocno];
	if (pgxact->vacuumFlags & PROC_IS_AUTOVACUUM)
	{
		return true;
	}

	waitProcLock = proc->waitProcLock;
	waitLock = waitProcLock->tag.myLock;

	return waitLock->tag.locktag_type == LOCKTAG_RELATION_EXTEND ||
		   waitLock->tag.locktag_type == LOCKTAG_PAGE ||
		   waitLock->tag.locktag_type == LOCKTAG_SPECULATIVE_TOKEN;
}