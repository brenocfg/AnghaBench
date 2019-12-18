#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  Event; int /*<<< orphan*/  RecordQueue; } ;
struct TYPE_6__ {void* Data; int /*<<< orphan*/ * ParseProc; int /*<<< orphan*/  Tick; } ;
typedef  int /*<<< orphan*/  RECORD_PARSE_PROC ;
typedef  TYPE_1__ RECORD ;
typedef  TYPE_2__ LOG ;

/* Variables and functions */
 int /*<<< orphan*/  InsertQueue (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  LockQueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Tick64 () ; 
 int /*<<< orphan*/  UnlockQueue (int /*<<< orphan*/ ) ; 
 TYPE_1__* ZeroMalloc (int) ; 

void InsertRecord(LOG *g, void *data, RECORD_PARSE_PROC *proc)
{
	RECORD *rec;
	// Validate arguments
	if (g == NULL || data == NULL || proc == NULL)
	{
		return;
	}

	rec = ZeroMalloc(sizeof(RECORD));
	rec->Tick = Tick64();
	rec->ParseProc = proc;
	rec->Data = data;

	LockQueue(g->RecordQueue);
	{
		InsertQueue(g->RecordQueue, rec);
	}
	UnlockQueue(g->RecordQueue);

	Set(g->Event);
}